// Description: client file of a server that works with RMI connection.
// To execute type in terminal in the directory above /src: javac Client.java <DESTINATION_ADDRESS> <PERMISSION>
// PERMISSION = 'professor' or 'student'

package rmi;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;
import rmi.RMI_Interface;


public class Client {

	private static String GREETING_MESSAGE = "\nHere are the commands the server can interpret:\n" +
			"\"all list\" - prints list of id and title of every discipline in the database\n" +
			"\"all info\" - prints id, title, menu, schedule and commentary of every discipline in the database\n" +
			"\"discipline_id title\" - prints title of discipline of given id (*)\n" +
			"\"discipline_id menu\" - prints menu of discipline of given id (*)\n" +
			"\"discipline_id schedule\" - prints schedule of discipline of given id (*)\n" +
			"\"discipline_id commentary\" - prints commentary of discipline of given id (*)\n" +
			"\"discipline_id addCommentary\" - makes request to add commentary to discipline of given id (only professors allowed) (*)\n" + 
			"* if the given discipline id exists on the database\n" +
			"Obs.: you can get every discipline_id with the command \"all list\"\n\n"; 
	
	private static String ERROR_MESSAGE = "Invalid command.\n" + GREETING_MESSAGE;
	
	public static void main(String args[]) {
		
        String input = new String();
        Scanner sc = new Scanner(System.in);
        String user_permission = null;
        String discipline_id = null,
        	   request_type = null,
        	   commentary  = null;
		
		if (args.length != 2) {
			System.out.println("Wrong input. Should be \"javac Client.java <DESTINATION_ADDRESS> <PERMISSION>\".\n" +
							   "PERMISSION = 'professor' or 'student'.");
			sc.close();
			return;
		}
		
		user_permission = args[1];
		
		//if (System.getSecurityManager() == null) {
          //  System.setSecurityManager(new SecurityManager());
        //}
		
        try {
            String name = "DisciplinesDB";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            RMI_Interface server_interface = (RMI_Interface) registry.lookup(name);
        	System.out.print(GREETING_MESSAGE);

            while (true) {
            	
            	input = sc.nextLine();
            	String[] inputList = input.split(" ");
            	discipline_id = inputList[0];
            	request_type = inputList[1];
            	
            	if (discipline_id.equals("all")) {
            		if (request_type.equals("list")) {
            			System.out.println(server_interface.getAllDisciplinesList());
            		} else if (request_type.equals("info")) {
            			System.out.print(server_interface.getAllDisciplinesList());
            		} else {
            			System.out.print(ERROR_MESSAGE);
            		}
            	} else {
            		if (request_type.equals("title")) {
            			System.out.print(server_interface.getDisciplineTitle(discipline_id));
            		} else if (request_type.equals("menu")) {
            			System.out.print(server_interface.getDisciplineMenu(discipline_id));
            		} else if (request_type.equals("schedule")) {
            			System.out.print(server_interface.getDisciplineSchedule(discipline_id));
            		} else if (request_type.equals("commentary")) {
            			System.out.print(server_interface.getDisciplineCommentary(discipline_id));
            		} else if (request_type.equals("addCommentary")) {
            			if (!user_permission.equals("professor")) {
            				System.out.println("Sorry, you have to have 'professor' permission to make this request.");
            			} else {
            				commentary = input.substring(inputList[0].length() + inputList[1].length() + 2);
            				System.out.print(server_interface.addCommentary(discipline_id, commentary));
            			}
            		} else {
            			System.out.print(ERROR_MESSAGE);
            		}
            	}
            }
            	
        } catch (Exception e) {
            System.err.print("-> WARNING: Error: ");
            e.printStackTrace();
        }

        sc.close();
	}
}
