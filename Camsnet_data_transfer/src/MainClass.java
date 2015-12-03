
public class MainClass {
	public static void main(String args[]){
		
//		File_Handler fh=new File_Handler("C:\\AdaptiveCameraNetworkPack\\CamNetPlat\\Camsnet_data_transfer\\camera_6_data.txt","camera_node_6");
//		fh.setDb_connection_string("jdbc:mysql://localhost:3306/");       //the database name is "camera"
//		fh.file_action();

        File_Handler fh=new File_Handler("C:\\AdaptiveCameraNetworkPack\\DBHandling\\Camsnet_data_transfer\\camera_22_data.txt","camera_node_22");
		fh.setDb_connection_string("jdbc:mysql://localhost:3306/");
		fh.file_action();

		fh=new File_Handler("C:\\AdaptiveCameraNetworkPack\\DBHandling\\Camsnet_data_transfer\\camera_28_data.txt","camera_node_28");
		fh.setDb_connection_string("jdbc:mysql://localhost:3306/");
		fh.file_action();

		/*File_Handler fh1=new File_Handler(""<give the next file of other camera node>"",""give the next table name"");
		fh.setDb_connection_string("jdbc:mysql://localhost:3306/");       //the database name is "camera"
		fh.file_action();*/
		
		/*File_Handler fh1=new File_Handler(""<give the next file of other camera node>"",""give the next table name"");
		fh.setDb_connection_string("jdbc:mysql://localhost:3306/");       //the database name is "camera"
		fh.file_action();*/
		
		/*File_Handler fh1=new File_Handler(""<give the next file of other camera node>"",""give the next table name"");
		fh.setDb_connection_string("jdbc:mysql://localhost:3306/");       //the database name is "camera"
		fh.file_action();*/
		
		//do for all 8 camera nodes
		}
			
	}
	

