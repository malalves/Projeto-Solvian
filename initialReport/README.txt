Submission Model - Latex - v1.0.0
----------------------------------
Testado no ambiente TeXworks (MiKTeX 2.9)

Texto codificado com ISO 8859-1 (latin1). Dependendo do programa usado para abrir o arquivo � necess�rio mudar o Encoding default UFT-8 para ISO 8859-1 e atualizar a p�gina.

Todas as modifica��es s�o realizadas no arquivo *.tex
----------------------------------
How-to-edit

* 'Dados da Proposta'.
Modificar apenas o necess�rio de cada campo, por exemplo:
\textbf{Nome do Projeto:} T�tulo projeto\\ -- Apenas substituir o trecho 'T�tulo projeto', deixando a marca��o inicial e a dupla barra invertida final (\\).

* 'Identifica��o e hist�rico da equipe'
Item \paragrafo... pode ser removido

Para cada membro da equipe (aluno e orientador) usar o comando \idEquipe para cada um, respeitando a ordem e conte�do dos argumentos.
\idEquipe{Nome}{Descri��o.}  -- Editar campos 'Nome' e 'Descri��o', mantendo as chaves

* 'Descri��o do sistema' e 'Justificativa'
Item \paragrafo... pode ser removido

Acrescentar cada novo par�grafo usando o comando \paragrafo{texto}

* 'Cronograma'
N�o retirar as barras invertidas ao final de cada item do cronograma