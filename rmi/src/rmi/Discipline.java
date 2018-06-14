package rmi;
import java.util.ArrayList;

public class Discipline {

	private String id;
	private String title;
	private String menu;
	private String schedule;
	private String commentary;
	
	
	private Discipline(String id, String title, String menu,
					  String schedule, String commentary) {
		this.id = id;
		this.title = title;
		this.menu = menu;
		this.schedule = schedule;
		this.commentary = commentary;
		
	}

	public static ArrayList<Discipline> generate() {
		// Instancia uma ArrayList de Disciplinas
		
		ArrayList<Discipline> disciplines = new ArrayList<Discipline>();
		
		disciplines.add(new Discipline("MC102\0",
								"Algoritmos e Programação de Computadores\0",
								"Conceitos básicos de organização de computadores.\0",
								"Seg 10h-12h / Ter 10h-12h / Qui 10h-12h\0",
								"\0"));
		
		disciplines.add(new Discipline("MC202\0",
								"Estruturas de Dados\0",
								"Estruturas básicas para representação de informações: listas, árvores, grafos e suas generalizações.\0",
								"Ter 10h-12h / Qui 10h-12h / Qui 14h-16h\0",
								"\0"));
		
		disciplines.add(new Discipline("MC358\0",
								"Fundamentos Matemáticos da Computação\0",
								"Conceitos básicos de matemática discreta e de lógica para computação.\0",
								"Ter 19h-21h / Qua 19h-21h\0",
								"\0"));
		
		disciplines.add(new Discipline("MC536\0",
								"Bancos de Dados: Teoria e Prática\0",
								"Arquiteturas de sistemas de gerenciamento de bancos de dados.\0",
								"Ter 19h-21h / Qui 19h-23h\0",
								"\0"));
		
		disciplines.add(new Discipline("MC833\0",
								"Programação de Redes de Computadores\0",
								"Programação utilizando diferentes tecnologias de comunicação: sockets, TCP e UDP, e chamada de método remoto.\0",
								"Qui 10h-12h\0",
								"\0"));
		
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
