package rmi;
// Description: server that works with RMI connection.
// To execute type in terminal in the directory above /src: javac Server.java

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

import rmi.RMI_Interface;

public class Server implements RMI_Interface {

	private static ArrayList<Discipline> disciplines;
	
	public Server() {
		super();
	}
	
	public static void main(String args[]) {
		
		disciplines = Discipline.generate();
		
		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}
		
		try {
			String name = "DisciplinesDB";
			RMI_Interface rmi_engine = new Server();
			RMI_Interface stub = (RMI_Interface) UnicastRemoteObject.exportObject(rmi_engine, 0);

			Registry registry = LocateRegistry.getRegistry();
			registry.rebind(name, stub);
			System.out.println("Server bound");
		} catch (Exception e) {
			System.err.println("Server error: ");
			e.printStackTrace();
		}
	}
	
	public Discipline getDiscipline(String discipline_id) {
		Discipline disc = null;
		
		for(int i = 0 ; i < disciplines.size(); i++) {
			if(discipline_id.equals(disciplines.get(i).getId())) {
				disc = disciplines.get(i);
			}
		}
		
		return disc;
	}
	
	public String getAllDisciplinesList() throws RemoteException {
		
		String output = new String();
		output = "";
		
		for (int i = 0; i < disciplines.size(); i++) {
			output.concat(disciplines.get(i).getId() + " - " + disciplines.get(i).getTitle() + "\n");
		}
		
		return output;
	}

	public String getAllDisciplinesInfos() throws RemoteException {
		
		String output = "";
		
		for(int i = 0; i < disciplines.size(); i++) {
			
			output.concat(disciplines.get(i).getId() + " - " + disciplines.get(i).getTitle() + "\n" +
						"- Menu :" + disciplines.get(i).getMenu() + "\n" +
						"- Schedule:" + disciplines.get(i).getSchedule() + "\n" +
						"- Commentary: " + disciplines.get(i).getCommentary() + "\n\n");
		}
		
		return output;
	}
	
	public String getDisciplineTitle(String discipline_id) throws RemoteException {
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.";
		}
		
		return "- Title: " + disc.getTitle() + "\n";
		
	}

	public String getDisciplineMenu(String discipline_id) throws RemoteException {

Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.";
		}
		
		return "- Menu: " + disc.getMenu() + "\n";
	}
	
	public String getDisciplineSchedule(String discipline_id) throws RemoteException {
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.";
		}
		
		return "- Schedule: " + disc.getSchedule() + "\n";
	}

	public String getDisciplineCommentary(String discipline_id) throws RemoteException {
Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.";
		}
		
		return "- Commentary: " + disc.getCommentary() + "\n";
	}

	public String addCommentary(String discipline_id, String commentary) throws RemoteException {

		Discipline disc = this.getDiscipline(discipline_id);
		
		if (commentary == null) {
			return "Invalid commentary.";
		}
		
		disc.setCommentary(commentary);
		
		return "Commentary added successfully.";
	}

}
