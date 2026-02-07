import express from 'express';
import { spawn } from 'child_process';
import cors from 'cors';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

// Necessário para ES Modules (substitui __dirname)
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const PORT = process.env.PORT || 3003;

app.use(cors());

// Servir arquivos estáticos do diretório public
app.use(express.static(path.join(__dirname, '../public')));

// Rota para executar o binário com argumentos passados como query params
app.get('/run', (req, res) => {
  // Parsear e validar todos os parâmetros
  const n = parseInt(req.query.n, 10);
  const populationSize = parseInt(req.query.populationSize, 10);
  const tournamentSize = parseInt(req.query.tournamentSize, 10);
  const elitismRate = parseFloat(req.query.elitismRate);
  const mutationRate = parseFloat(req.query.mutationRate);
  const selectionType = parseInt(req.query.selectionType, 10);
  const crossoverType = parseInt(req.query.crossoverType, 10);
  const maxRounds = parseInt(req.query.maxRounds, 10);

  // Validação
  if (!Number.isFinite(n) || n < 4) {
    return res.status(400).json({ error: 'Tamanho do tabuleiro inválido. Use ?n=4 ou maior' });
  }
  if (!Number.isFinite(populationSize) || populationSize < 1) {
    return res.status(400).json({ error: 'Tamanho da população inválido' });
  }
  if (!Number.isFinite(tournamentSize) || tournamentSize < 1) {
    return res.status(400).json({ error: 'Tamanho do torneio inválido' });
  }
  if (!Number.isFinite(elitismRate) || elitismRate < 0 || elitismRate > 1) {
    return res.status(400).json({ error: 'Taxa de elitismo deve estar entre 0 e 1' });
  }
  if (!Number.isFinite(mutationRate) || mutationRate < 0 || mutationRate > 1) {
    return res.status(400).json({ error: 'Taxa de mutação deve estar entre 0 e 1' });
  }
  if (![1, 2, 3, 4].includes(selectionType)) {
    return res.status(400).json({ error: 'Tipo de seleção deve ser 1, 2, 3 ou 4' });
  }
  if (![1, 2].includes(crossoverType)) {
    return res.status(400).json({ error: 'Tipo de cruzamento deve ser 1 ou 2' });
  }
  if (!Number.isFinite(maxRounds) || maxRounds < 1) {
    return res.status(400).json({ error: 'Número de rodadas inválido' });
  }

  const child = spawn(path.join(__dirname, '../../backend/nrainhas.exe'), [], {
    cwd: path.join(__dirname, '../../backend')
  });
  
  let stdout = '';
  let stderr = '';
  let responseEnviado = false;
  let timeout;
  
  // Timeout de 60 segundos
  timeout = setTimeout(() => {
    if (!responseEnviado) {
      responseEnviado = true;
      child.kill();
      res.status(500).json({ error: 'Timeout: programa demorou muito tempo para responder' });
    }
  }, 60000);
  
  child.stdout.on('data', (data) => {
    const texto = data.toString();
    stdout += texto;
  });
  
  child.stderr.on('data', (data) => {
    const texto = data.toString();
    stderr += texto;
  });
  
  child.on('error', (err) => {
    console.error('Erro ao iniciar processo:', err);
    clearTimeout(timeout);
    if (!responseEnviado) {
      responseEnviado = true;
      res.status(500).json({ error: `Erro ao iniciar: ${err.message}` });
    }
  });
  
  child.on('close', (code) => {
    clearTimeout(timeout);
    
    if (responseEnviado) return;
    responseEnviado = true;
    
    if (code !== 0) {
      console.error('Stderr:', stderr);
      return res.status(500).json({ error: `Programa retornou código ${code}` });
    }

    // Ler arquivo dadosNRainhas.txt
    const filePath = path.join(__dirname, '../../backend', 'dadosNRainhas.txt');
    
    try {
      const fileContent = fs.readFileSync(filePath, 'utf-8');
      
      const lines = fileContent.split('\n');
      const byFitness = [];
      const byGeneration = [];
      let executionTime = null;
      
      let mode = null; // 'fitness' ou 'generation'
      let skipNext = false;
      
      for (let i = 0; i < lines.length; i++) {
        const line = lines[i].trim();
        
        // Pular linhas vazias
        if (!line) continue;
        
        // Detectar início da seção de fitness
        if (line.includes('=== INDIVIDUOS POR NIVEL DE FITNESS ===')) {
          mode = 'fitness';
          skipNext = true; // Próxima linha é o cabeçalho
          continue;
        }
        
        // Detectar início da seção de geração
        if (line.includes('=== MELHORES INDIVIDUOS POR GERACAO')) {
          mode = 'generation';
          skipNext = true; // Próxima linha é o cabeçalho
          continue;
        }
        
        // Pular cabeçalho (Fitness Geracao Individuo)
        if (skipNext) {
          skipNext = false;
          continue;
        }
        
        // Tentar parsear o tempo de execução
        if (line.includes('Tempo para encontrar melhor fitness:')) {
          const match = line.match(/(\d+)\s*ms\s*\(([0-9.]+)\s*segundos\)/);
          if (match) {
            executionTime = {
              milliseconds: parseInt(match[1], 10),
              seconds: parseFloat(match[2])
            };
          }
          continue;
        }
        
        // Sair do modo se encontrar outra seção ===
        if (line.startsWith('===')) {
          mode = null;
          continue;
        }
        
        // Processar dados
        if (mode === 'fitness') {
          const parts = line.split(/\s+/);
          if (parts.length >= 3) {
            const fitness = parseInt(parts[0], 10);
            const generation = parseInt(parts[1], 10);
            const positions = parts.slice(2).map(Number).filter(n => !isNaN(n));
            
            if (!isNaN(fitness) && !isNaN(generation) && positions.length > 0) {
              byFitness.push({ fitness, generation, positions });
            }
          }
        } else if (mode === 'generation') {
          const parts = line.split(/\s+/);
          if (parts.length >= 3) {
            const generation = parseInt(parts[0], 10);
            const fitness = parseInt(parts[1], 10);
            const positions = parts.slice(2).map(Number).filter(n => !isNaN(n));
            
            if (!isNaN(fitness) && !isNaN(generation) && positions.length > 0) {
              byGeneration.push({ fitness, generation, positions });
            }
          }
        }
      }
      
      res.json({ 
        n, 
        byFitness, 
        byGeneration,
        total: byFitness.length + byGeneration.length,
        executionTime
      });
      
    } catch (err) {
      console.error('Erro ao ler arquivo:', err);
      return res.status(500).json({ error: `Erro ao ler arquivo: ${err.message}` });
    }
  });

  // Enviar parâmetros para o executável na ordem correta
  // 1. n, 2. populationSize, 3. selectionType, 
  // 4. tournamentSize (só se selectionType == 3 ou 4),
  // 5. elitismRate, 6. mutationRate, 7. crossoverType, 8. maxRounds
  const params = [n, populationSize, selectionType];
  
  // Adiciona tournamentSize apenas se seleção for Torneio (3) ou Dissimilares (4)
  if (selectionType === 3 || selectionType === 4) {
    params.push(tournamentSize);
  }
  
  params.push(elitismRate, mutationRate, crossoverType, maxRounds);
  
  let i = 0;
  
  const sendNext = () => {
    if (i < params.length) {
      child.stdin.write(String(params[i]) + '\n');
      i++;
      setTimeout(sendNext, 50);
    } else {
      child.stdin.end();
    }
  };
  
  try {
    sendNext();
  } catch (err) {
    console.error('Erro ao enviar dados:', err);
    if (!responseEnviado) {
      responseEnviado = true;
      clearTimeout(timeout);
      res.status(500).json({ error: `Erro ao enviar dados: ${err.message}` });
    }
  }
});

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
