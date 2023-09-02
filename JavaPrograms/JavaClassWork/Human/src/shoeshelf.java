import java.util.ArrayList;
import java.util.*;
public class shoeshelf 
{
	ArrayList<shoe> x;
	public shoeshelf()
	{
		x= new ArrayList<shoe>();
	}
	public shoe getshoe(int num)
	{
		return x.get(num);
	}
	public void addshoe(shoe x)
	{
		this.x.add(x);
	}
	public void removeshoe(int num)
	{
		x.remove(num);
	}
	public void displayallshoes()
	{
		for(shoe a:x)
		{
			System.out.print(a);
		}
	}

}
