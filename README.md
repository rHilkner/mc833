# MC833

Projects from the discipline Computer Network - MC833 (State University of Campinas - UNICAMP) with the objective of building a server (TCP, UDP & RMI) that holds a (fake-ish) database of disciplines of our university and that can exchange messages with some client that can make requests about any disciplines (such as: getting a list of every disciplines with its titles; getting a list of all information available of every discipline; getting a discipline title, menu, schedule or commentary).

If you want to execute the code, you must generate a server executable file (you can just go to the server folder via terminal and execute "make", the Makefile will generate the executable) and a client executable file. Run first the server ("./server" or equivalent) and after that you can run the client file by informing the server's internet IP address and PORT in the 2nd and 3rd arguments of the execution (equivalent to "./client 192.168.77.10 8888" or so).

"\nHere are the commands the server can interpret:\n\
\"all list\" - prints list of id and title of every discipline in the database\n\
\"all info\" - prints id, title, menu, schedule and commentary of every discipline in the database\n\
\"discipline_id title\" - prints title of discipline of given id (*)\n\
\"discipline_id menu\" - prints menu of discipline of given id (*)\n\
\"discipline_id schedule\" - prints schedule of discipline of given id (*)\n\
\"discipline_id commentary\" - prints commentary of discipline of given id (*)\n\
\"discipline_id addCommentary\" - makes request to add commentary to discipline of given id (only professors allowed) (*)\n\
* if the given discipline id exists on the database\n\
Obs.: you can get every discipline_id with the command \"all list\"\n\n";

When running the application you will find a breaf tutorial in the first welcome messages, but in summarize you are able to make the following commands:
• "all list" - Prints list of id and title of every discipline in the database;
• "all info" - Prints id, title, menu, schedule and commentary of every discipline in the database
• "discipline_id title" - Prints title of discipline of given id (*)
• "discipline_id menu" - Prints menu of discipline of given id (*)
• "discipline_id schedule" - Prints schedule of discipline of given id (*)
• "discipline_id commentary" - Prints commentary of discipline of given id (*)
• "discipline_id addCommentary" - Makes request to add commentary to discipline of given id (only professors allowed) (*)
* if the given discipline id exists on the database
