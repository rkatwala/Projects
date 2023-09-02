public class shoe 
{
	private String name;
	private int size;
	private String color;
	private sock [] x= new sock [2];
	
	public shoe(String name, int size, String color, sock leftsock, sock rightsock)
	{
		this.name= name;
		this.size= size;
		this.color= color;
		x[0]= leftsock;
		x[1]= rightsock;
	}
	
	public void setleftsock(sock leftsock)
	{
		x[0]= leftsock;
	}
	
	public void setrightsock(sock rightsock)
	{
		x[1]= rightsock;
	}
	
	public sock getleftsock()
	{
		return x[0];
	}
	
	public sock getrightsock()
	{
		return x[1];
	}
	public String color() {
		return color;
	}
	public void setcolor(String color) {
		this.color=color;
	}
	
}
