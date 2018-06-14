package rmi;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMI_Interface extends Remote {

	public String getAllDisciplinesList() throws RemoteException;
	public String getAllDisciplinesInfos() throws RemoteException;
	public String getDisciplineTitle(String discipline_id) throws RemoteException;
	public String getDisciplineMenu(String discipline_id) throws RemoteException;
	public String getDisciplineSchedule(String discipline_id) throws RemoteException;
	public String getDisciplineCommentary(String discipline_id) throws RemoteException;
	public String addCommentary(String discipline_id, String commentary) throws RemoteException;
	
}
