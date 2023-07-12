<h1 align="center">
Trabalho 3 – Árvores Binárias de Busca </h1>
<h3 align="left"> 
    Informações Gerais:
</h3>
• Data Limite de Entrega: 19/07/2023 (23:59).<br>
• Pontuação: 10 pontos (20% da nota do semestre).<br>
• Formato de Entrega: O trabalho será entregue via uma série de atividades no sistema
de correção automática Testr.<br>
• Os trabalhos devem ser desenvolvidos individualmente.<br>
• Importante: Trabalhos entregues após a data limite sem justificativa com comprovação
documental (atestado médico, etc.), ou que não estiverem de acordo com a especificado
receberão nota zero.<br>
<h3 align="left"> 
    Descrição:
</h3>
O trabalho consiste na implementação de uma árvore binária de busca e funções para sua
manipulação e utilização como dicionário e fila de prioridade. Devem ser providas funções para:<br><br>
• Inserção e atualização de pares chave-valor.<br>
• Obtenção de um valor a partir de uma chave. Se a chave não existir, deve ser retornado
NULL.<br>
• Remoção de um par chave-valor a partir da chave. A função deve retornar o par.<br>
• Obtenção do par chave-valor da maior chave. Nesta operação, o par deve ser retornado,
mas mantido na árvore.<br>
• Obtenção do par chave-valor da menor chave. Nesta operação, o par deve ser retornado,
mas mantido na árvore.<br>
• Extração do par chave-valor da maior chave. Ao final desta operação, o par deve ser
removido da árvore e retornado.<br>
• Extração do par chave-valor da menor chave. Ao final desta operação, o par deve ser
removido da árvore e retornado.<br><br>
Além da estrutura de árvore, devem ser providas funções para retornar os itens da árvore binária
como um vetor de pares chave-valor de acordo com os seguintes métodos de travessia pela
árvore:<br><br>
• Inorder Traversal: Visita o nó atual depois de visitar todos os nós dentro da subárvore
esquerda, mas antes de visitar qualquer nó dentro da subárvore direita.<br>
• Preorder Traversal: Visita o nó atual antes de visitar qualquer nó dentro das subárvores
esquerda ou direita.<br>
• Postorder Traversal: Visita o nó atual depois de visitar todos os nós das subárvores
esquerda e direita.<br>
• Level Order Traversal: Visita os nós nível a nível e da esquerda para a direita, um nível de
cada vez.<br><br>
Para os três primeiros métodos devem ser providas duas versões, uma recursiva e uma iterativa.
As estruturas de dados devem ser opacas e genéricas.<br>
