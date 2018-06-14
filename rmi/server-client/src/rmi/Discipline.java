package rmi;
import java.util.ArrayList;

public class Discipline {

	private String id;
	private String title;
	private String menu;
	private String schedule;
	private String commentary;
	
	
	private Discipline(String id, String title, String menu, String schedule, String commentary) {
		this.id = id;
		this.title = title;
		this.menu = menu;
		this.schedule = schedule;
		this.commentary = commentary;
		
	}

	public static ArrayList<Discipline> generate() {
		// Instancia uma ArrayList de Disciplinas
		
		ArrayList<Discipline> disciplines = new ArrayList<Discipline>();
		
		disciplines.add(new Discipline("MC102",
								"Algoritmos e Programação de Computadores",
								"Conceitos básicos de organização de computadores.",
								"Seg 10h-12h / Ter 10h-12h / Qui 10h-12h",
								""));
		
		disciplines.add(new Discipline("MC202",
								"Estruturas de Dados",
								"Estruturas básicas para representação de informações: listas, árvores, grafos e suas generalizações.",
								"Ter 10h-12h / Qui 10h-12h / Qui 14h-16h",
								""));
		
		disciplines.add(new Discipline("MC358",
								"Fundamentos Matemáticos da Computação",
								"Conceitos básicos de matemática discreta e de lógica para computação.",
								"Ter 19h-21h / Qua 19h-21h",
								""));
		
		disciplines.add(new Discipline("MC536",
								"Bancos de Dados: Teoria e Prática",
								"Arquiteturas de sistemas de gerenciamento de bancos de dados.",
								"Ter 19h-21h / Qui 19h-23h",
								""));
		
		disciplines.add(new Discipline("MC833",
								"Programação de Redes de Computadores",
								"Programação utilizando diferentes tecnologias de comunicação: sockets, TCP e UDP, e chamada de método remoto.",
								"Qui 10h-12h",
								""));
		
		return disciplines;
	}

	public String getId() {
		return id;
	}
	
	public String getTitle() {
		return title;
	}
	
	public String getMenu() {
		return menu;
	}

	public String getSchedule() {
		return schedule;
	}

	public String getCommentary() {
		return commentary;
	}
	
	public void setCommentary(String commentary) {
		this.commentary = commentary;
	}
	
}
