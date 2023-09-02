// Rahul Katwala
import java.util.*;
public class Madlibs {
	public static void main(String[] args) {
		// placing scanner
		Scanner penn = new Scanner (System.in);
		// all variables for the strings
		String a,c,d,e,f,g,h,i,j,tt,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
		// all variables for the ints
		int num,aa,bb,cc,dd,ee,aaa,sss,age,wolves, ww,qq,bbb;
		
		// Getting all the inputs for all the variables to plug in the code
		System.out.println("Give me a number");
		aa = penn.nextInt();
		penn.nextLine();
		
		System.out.println("Give me an adjective");
		a = penn.next();
		penn.nextLine();
		
		// getting two numbers for mathematically altered number 
		System.out.println("Give a number");
		aaa=penn.nextInt();
		penn.nextLine();
		System.out.println("Give a number");
		sss= penn.nextInt();
		
		// age will be the number output
		age= (aaa+sss)/2;
	
		
		System.out.println("Give me a number");
		num = penn.nextInt();
		penn.nextLine();
		
		System.out.println("Give me a place");
		c = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a verb");
		d = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a verb");
		e = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a number");
		bbb = penn.nextInt();
		penn.nextLine();
		
		System.out.println("Give me a noun");
		f = penn.next();
		penn.nextLine();
		
		System.out.println("Give me an adjective");
		g = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a number");
		bb = penn.nextInt();
		penn.nextLine();
		
		System.out.println("Give me a noun");
		h = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a phrase a mother would say");
		i = penn.nextLine();
		
		System.out.println("Give me a past tense verb");
		j = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a liquid");
		tt = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a number");
		cc = penn.nextInt();
		penn.nextLine();
		
		System.out.println("Give me an adjective");
		k = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a verb");
		l = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a past tense verb");
		m = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a past tense verb");
		n = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a one word building material");
		o = penn.next();
		penn.nextLine();
		
		System.out.println("Give me an adjective");
		p = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a number");
		dd = penn.nextInt();
		penn.nextLine();
		

		System.out.println("Give me a weapon and if number chosen before was greater than 1, make the weapon plural");
		q = penn.next();
		penn.nextLine();
		

		System.out.println("Give me a noise");
		r = penn.next();
		penn.nextLine();
		

		System.out.println("Give me a past tense verb");
		t = penn.next();
		penn.nextLine();
		

		System.out.println("Give me a color");
		u = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a number");
		ww=penn.nextInt();
		penn.nextLine();
		System.out.println("Give me a number");
		qq= penn.nextInt();
		
		// wolves will be the number output
		wolves= (ww+qq)*2;
		

		System.out.println("Give me an adjective");
		v = penn.next();
		penn.nextLine();
		

		System.out.println("Give me a past tense verb");
		w = penn.next();
		penn.nextLine();
		

		System.out.println("Give me a noun");
		x = penn.next();
		penn.nextLine();
		
		System.out.println("Give me a verb ending with ing");
		y = penn.next();
		penn.nextLine();
		
		System.out.println("Give me an adjective");
		z = penn.next();
		penn.nextLine();
		
		// printing story with all the inputs plugged in
		System.out.println("\tOnce upon a time, there was " + aa +" "+  a + " pigs all of age " + age +".\n " + num +" days later, the mother told them they had to move out of the " + c + " and " + d+ " by themselves.\n The piggies then decided to "+ e +" and found "+ bbb + " " + f+". They then made a " +g+ " village and had \n houses for themselves. In total there was around " + bb + " animals living there. One day the pigs were \n talking around a " +h+ " and remembered how their mom told them “" +i+"”. The pigs then " +j+ " and drank "+ tt +" for \n "+cc +" hours and went back home. The next day a " + k +" wolf comes to the village and knocks on one of \n the piggies door. He tells the piggie “let me in or I will " + l + " your house away.” The piggie said no \n so the wolf went and " + m + " the piggie. He then " + n+ " down the village to the house made up of " + o + ". \n The piggy there was "+p+  ", but the piggy used his "+dd+ " " +q+ " to get rid of the wolf. \n The other piggies heard the "+r+" of the incident and all "+t+ " with the hero piggy. The wolf was \n now " +u+ " from the event and told " +wolves+  " other wolves of what happened. The "+v+ " wolves \n then " +w+ " all the piggies. The pigs’ " +x+ " were no match for them. All the pigs ended up "+y+ " and \n never challenged the " +z+ " wolves again. The end.");
		// The end

	}
}
