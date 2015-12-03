import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import com.mysql.jdbc.Statement;

public class File_Handler {

	Connection conn = null;
	Statement statement;
	String table_name = null;
	String db_connection_string=null;
	String table_creation= new String();
	File file;	
	String db_name=new String("camera");
	int sql_ini_length=0;
	int sql_second_length;
	
	public void setDb_connection_string(String db_connection_string) {
		this.db_connection_string = db_connection_string;
	}

	StringBuilder value_stting = new StringBuilder("");

	public File_Handler(String filepath,String table_name) {
		this.file = new File(filepath);
		this.table_name= new String(table_name);
		
	}
	
	public void file_action(){
	try {
			
			conn = DriverManager.getConnection(db_connection_string + db_name, "root", "");
			if (conn != null)
				System.out.println("The connection is open");

		} catch (SQLException ex) {
			// handle any errors
			System.out.println("SQLException: " + ex.getMessage());
			System.out.println("SQLState: " + ex.getSQLState());
			System.out.println("VendorError: " + ex.getErrorCode());
		}
	table_creation=table_creation+ "CREATE TABLE `"
			+ table_name
			+ "` ( `Record_ID` int(11) NOT NULL, `Video_ID` int(11) NOT NULL, `Profile_ID` varchar(10) NOT NULL, `TimeStamp` double NOT NULL, `Blob_Center_Point` varchar(10) NOT NULL, PRIMARY KEY (`Record_ID`)) ENGINE=InnoDB DEFAULT CHARSET=latin1";
	try {
		statement=(Statement) conn.createStatement();		
		System.out.println(table_creation);
		statement.executeUpdate(table_creation);
		
	} catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	StringBuilder sql= new StringBuilder("INSERT INTO"
			+ " `"
			+ table_name
			+ "`"
			+ "(`Record_ID`, `Video_ID`, `Profile_ID`, `TimeStamp`, `Blob_Center_Point`) "
			+ "VALUES ");
	 sql_ini_length=sql.length();
			
		try {			
			FileReader fileReader = new FileReader(file);
			BufferedReader bufferedReader = new BufferedReader(fileReader);			
			String line;
			int record_id=1;
			while ((line = bufferedReader.readLine()) != null) {
				//System.out.println(line);
				line = line.trim();
				String [] split_line= line.split(" ");
				if (split_line.length == 3) {
					value_stting.append("("
							+ Integer.toString(record_id) + ","
							+ split_line[0] + ",'"
							+ split_line[1] + "'," + split_line[2] + ",'"
							+ "MISSING" + "')");
				}
				else if (split_line.length == 4){
					value_stting.append("("
							+ Integer.toString(record_id) + ","
							+ split_line[0] + ",'"
							+ split_line[1] + "'," + split_line[2] + ",'"
							+ split_line[3] + "')");
				}
				else{
					System.out.println("Somethings is not right");
				}

				sql.append(value_stting);
				sql_second_length=sql.length();
				//System.out.println(sql);
				try {
					statement=(Statement) conn.createStatement();
					String temp_sql= new String(sql);
					System.out.println(temp_sql);
					statement.executeUpdate(temp_sql);
					sql.delete(sql_ini_length,sql_second_length);
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				value_stting.delete(0, value_stting.length());
				record_id++;
			}
			System.out.println("Query Completed!");
			fileReader.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	

}
