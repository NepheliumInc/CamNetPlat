import com.mysql.jdbc.Statement;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * Created by dehandecroos on 11/20/2015.
 */
public class ProfileTimeRange {




    public void notYetAFunction() throws SQLException{

        String[] cameraIds = {"camera_node_6","camera_node_22"," camera_node_28"};
        String profileId = "1_6";
        String finalJoinQuery = "";
        for(String cameraId : cameraIds)
        {
            finalJoinQuery += "select * from "+ cameraId +" where profile_id='"+profileId+"' ";
        }

        String db_connection_string="jdbc:mysql://localhost:3306/";
        String  db_name = "camera";
        Connection conn = DriverManager.getConnection(db_connection_string + db_name, "root", "root");
        Statement statement=(Statement) conn.createStatement();
        ResultSet resultSet = statement.executeQuery(finalJoinQuery);
       // resultSet.getI

    }




}
