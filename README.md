Este sistema implementa um sistema de detecção de incêndios em uma floresta simulada, utilizando programação paralela com pthreads e monitores. A floresta é modelada como uma matriz 30x30, onde cada célula é monitorada por uma thread sensor que detecta e comunica incêndios. O sistema inclui sensores, que monitoram o estado de uma célula e utilizam mutexes para sincronização e exclusão mútua, gerador de incêndios, que deve iniciar um incêndio simulado a cada tres segundos, e central de controle, que recebe notificação do inicio do incêndio, e gera o combate as queimadas.
A comunicação entre threads é feita através de monitores para garantir sincronização, prevenção de condições de corrida e comunicação segura. A visualização da matriz é atualizada em tempo real no terminal, e eventos são registrados em um log para monitoramento e análise.
