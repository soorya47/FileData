
import java.util.Scanner;

public class FileRead {
	static {
	      System.loadLibrary("fileData"); 
	}
	      private native boolean addRow(String row,String s1,String s2, String s3, String s4);
	      private native boolean removeRow(String s1);
	      private native boolean updateRow(String r, String c, String n);
	      private native boolean searchRow(String c, String data);
	      public static void main(String[] args) {
	  		
	  		Scanner sc=new Scanner(System.in);
	  		FileRead obj =new FileRead();
			int i =1;
	  		while(true) {
	  			
	  			System.out.println("1.add \n 2.remove \n 3.update \n 4.search");
				int c=sc.nextInt();
				sc.nextLine();
	  			switch(c) {
	  			case 1: {
					System.out.println("name");
	  				String name=sc.nextLine();
					System.out.println("age");
	  				String age=sc.nextLine();
					System.out.println("date");
	  				String date=sc.nextLine();
					System.out.println("city");
	  				String city=sc.nextLine();
					
	  				obj.addRow(String.valueOf(i),name,age,date,city);
					i++;
	  			};break;
	  			
	  			case 2: {
					System.out.println("deleteRow");
	  				String row=sc.nextLine();
	  				obj.removeRow(row);
	  			};break;
	  			
	  			case 3: {
					System.out.println("Row");
	  				String row=sc.nextLine();
					System.out.println("1)name 2)age 3)dob 4)city");
	  				String col= sc.nextLine();
					System.out.println("data");
					String data=sc.nextLine();
	  				obj.updateRow(row,col,data);
	  			};break;
	  			
	  			case 4: {
					System.out.println("1)name 2)age 3)dob 4)city");
	  				String col=sc.nextLine();
					System.out.println("data");
					String data=sc.nextLine();
	  				if(obj.searchRow(col,data)){
						System.out.println("data is present");
					}
					else{
						System.out.println("data is not present");
					}
	  			};break;
	  			}
	  			}
	  		
	  		
	  	
	   }
}
