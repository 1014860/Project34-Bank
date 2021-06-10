import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.jcraft.jsch.JSch;
import com.jcraft.jsch.Session;
import com.mysql.jdbc.Driver;

import java.sql.Connection;


public class JDBC {

	/**
	 * Java Program to connect to the remote database through SSH using port forwarding
	 * @author Pankaj@JournalDev
	 * @throws SQLException 
	 */
	public static void main(String[] args) throws SQLException {

        int lport=7000;
        String rhost="145.24.222.59";
	    String host="145.24.222.59";
	    int rport=3306;
	    String user="ubuntu-1014860";
	    String password="Fmw883";
	    String dbuserName = "root";
        String dbpassword = "Wachtwoord123";
        String url = "jdbc:mysql://145.24.222.59:3306/money_makers";
        //String driverName="com.mysql.cj.jdbc.Driver";
        Connection conn = null;
        Session session= null;
	    try{
	    	//Set StrictHostKeyChecking property to no to avoid UnknownHostKey issue
	    	java.util.Properties config = new java.util.Properties(); 
	    	config.put("StrictHostKeyChecking", "no");
	    	JSch jsch = new JSch();
	    	session=jsch.getSession(user, host, 22);
	    	session.setPassword(password);
	    	session.setConfig(config);
	    	session.connect();
	    	System.out.println("Connected");
	    	int assigned_port=session.setPortForwardingL(lport, rhost, rport);
	        System.out.println("localhost:"+assigned_port+" -> "+rhost+":"+rport);
	    	System.out.println("Port Forwarded");
	    	
	    	//mysql database connectivity
            //Class.forName(driverName);
	    	
            conn = DriverManager.getConnection("jdbc:mysql://localhost:"+assigned_port+"/", dbuserName, dbpassword);
            System.out.println ("Database connection established");
            System.out.println("DONE");
            
            while(true) {
            	
            }
	    }catch(Exception e){
	    	e.printStackTrace();
	    }finally{
	    	if(conn != null && !conn.isClosed()){
	    		System.out.println("Closing Database Connection");
	    		conn.close();
	    	}
	    	if(session !=null && session.isConnected()){
	    		System.out.println("Closing SSH Connection");
	    		session.disconnect();
	    	}
            
	    }
	}

}