package rmi;
// Description: server that works with RMI connection.
// To execute type in terminal in the directory above /src: java Server.java

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
		
		//if (System.getSecurityManager() == null) {
		//	System.setSecurityManager(new SecurityManager());
		//}
		
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
		
		long startTime = System.nanoTime();
		
		String output = new String();
		output = "";
		
		for (int i = 0; i < disciplines.size(); i++) {
			output = output.concat(disciplines.get(i).getId() + " - " + disciplines.get(i).getTitle() + "\n");
		}
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);

		return output + "\n";
	}

	public String getAllDisciplinesInfos() throws RemoteException {
		
		long startTime = System.nanoTime();
		
		String output = "";
		
		for(int i = 0; i < disciplines.size(); i++) {
			
			output = output.concat(disciplines.get(i).getId() + " - " + disciplines.get(i).getTitle() + "\n" +
						"- Menu :" + disciplines.get(i).getMenu() + "\n" +
						"- Schedule:" + disciplines.get(i).getSchedule() + "\n" +
						"- Commentary: " + disciplines.get(i).getCommentary() + "\n\n");
		}
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);
		
		return output;
	}
	
	public String getDisciplineTitle(String discipline_id) throws RemoteException {
		
		long startTime = System.nanoTime();
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.\n\n";
		}
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);
		
		return "- Title: " + disc.getTitle() + "\n\n";
	}

	public String getDisciplineMenu(String discipline_id) throws RemoteException {

		long startTime = System.nanoTime();
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.\n\n";
		}
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);
		
		return "- Menu: " + disc.getMenu() + "\n\n";
	}
	
	public String getDisciplineSchedule(String discipline_id) throws RemoteException {
		
		long startTime = System.nanoTime();
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.\n\n";
		}
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);
		
		return "- Schedule: " + disc.getSchedule() + "\n\n";
	}

	public String getDisciplineCommentary(String discipline_id) throws RemoteException {
		
		long startTime = System.nanoTime();
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (disc == null) {
			return "Invalid discipline ID.\n\n";
		}
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);
		
		return "- Commentary: " + disc.getCommentary() + "\n\n";
	}

	public String addCommentary(String discipline_id, String commentary) throws RemoteException {

		long startTime = System.nanoTime();
		
		Discipline disc = this.getDiscipline(discipline_id);
		
		if (commentary == null) {
			return "Invalid commentary.\n\n";
		}
		
		disc.setCommentary(commentary);
		
		long deltaTime = System.nanoTime() - startTime;
		System.out.println(deltaTime);
		
		return "Commentary added successfully.\n\n";
	}

}
