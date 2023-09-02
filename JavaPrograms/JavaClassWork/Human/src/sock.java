
public class sock
{
	private boolean exists;
	private String color;
	public sock()
	{
		exists= false;
		color= "non existant";
	}
	public void setSock(String color)
	{
		this.color= color;
		exists= true;
	}
	public void removesock()
	{
		color= "non existant";
		exists = false;
	}
	public String toString()
	{
		return color;
	}

}