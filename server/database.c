#include <string.h>

#include "database.h"

discipline disciplines[] = {
	{
		.id = "MC102",
		.title = "Algoritmos e Programação de Computadores",
		.menu = "Conceitos básicos de organização de computadores. Construção de algoritmos e sua representação em pseudocódigo e linguagens de alto nível. Desenvolvimento sistemático e implementação de programas. Estruturação, depuração, testes e documentação de programas. Resolução de problemas.",
		.schedule = "Seg 10h-12h / Ter 10h-12h / Qui 10h-12h",
		.commentary = ""
	},
	
	{
		.id = "MC202",
		.title = "Estruturas de Dados",
		.menu = "Estruturas básicas para representação de informações: listas, árvores, grafos e suas generalizações. Algoritmos para construção, consulta e manipulação de tais estruturas. Desenvolvimento, implementação e testes de programas usando tais estruturas em aplicações específicas.",
		.schedule = "Ter 10h-12h / Qui 10h-12h / Qui 14h-16h",
		.commentary = ""
	},
	
	{
		.id = "MC358",
		.title = "Fundamentos Matemáticos da Computação",
		.menu = "Conceitos básicos de matemática discreta e de lógica para computação. Técnicas de provas, indução matemática. Relações e conceitos de teoria de grafos. Modelagem de problemas usando grafos.",
		.schedule = "Ter 19h-21h / Qua 19h-21h",
		.commentary = ""
	},
	
	{
		.id = "MC536",
		.title = "Bancos de Dados: Teoria e Prática",
		.menu = "Arquiteturas de sistemas de gerenciamento de bancos de dados. Modelagem de dados: modelos conceituais e lógicos, incluindo o modelo relacional e normalização. Álgebra relacional. Linguagens de definição e de manipulação de dados. Otimização de consultas. Mecanismos de proteção, recuperação e segurança. Controle de concorrência. Bancos de dados não relacionais. Projeto e desenvolvimento de ferramentas e técnicas utilizadas na solução de problemas de sistemas de informação, utilizando bancos de dados. Modelagem, especificação, projeto e implementação de aplicações em sistemas de informação.",
		.schedule = "Ter 19h-21h / Qui 19h-23h",
		.commentary = ""
	},
	
	{
		.id = "MC833",
		.title = "Programação de Redes de Computadores",
		.menu = "Programação utilizando diferentes tecnologias de comunicação: sockets, TCP e UDP, e chamada de método remoto.",
		.schedule = "Qui 10h-12h",
		.commentary = ""
	},

};


// Finds discipline with given id
discipline* findDiscipline(char discipline_id[]) {

	// Getting number of elements in disciplines array
	int db_length = sizeof(disciplines)/sizeof(discipline);

	// Searching for discipline with given id
	for (int i = 0; i < db_length; i++) {
		if (strcmp(disciplines[i].id, discipline_id) == 0) {
			return &disciplines[i];
		}
	}

	return NULL;
}

// discipline _ = {
// 	.id = "",
// 	.title = "",
// 	.menu = "",
// 	.schedule = "",
// 	.commentary = ""
// }
