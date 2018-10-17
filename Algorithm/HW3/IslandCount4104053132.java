
public class IslandCount4104053132 extends IslandCount{

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		IslandCount4104053132 A=new IslandCount4104053132();
		double time1, time2;
		time1 = System.currentTimeMillis();
		
		/*
		A.connect(1,2);
		A.connect(2,3);
		A.connect(2,4);
		A.connect(4,5);
		A.connect(6,7);
		*/
		
		/*
		A.connect(1,2);
		A.connect(2,3);
		A.connect(6,7);
		*/
		
		A.connect(1,6);
		A.connect(1,7);
		A.connect(2,7);
		A.connect(2,10);
		A.connect(3,5);
		A.connect(3,7);
		A.connect(4,8);
		A.connect(5,19);
		A.connect(5,33);
		A.connect(6,7);
		A.connect(6,8);
		A.connect(8,9);
		A.connect(9,13);
		A.connect(11,22);
		A.connect(11,49);
		A.connect(12,14);
		A.connect(14,18);
		A.connect(14,24);
		A.connect(15,16);
		A.connect(15,49);
		A.connect(17,25);
		A.connect(20,29);
		A.connect(20,30);
		A.connect(21,28);
		A.connect(22,23);
		A.connect(23,31);
		A.connect(26,47);
		A.connect(27,49);
		A.connect(28,35);
		A.connect(28,36);
		A.connect(32,37);
		A.connect(33,34);
		A.connect(34,37);
		A.connect(38,48);
		
		/*
		Scanner keyboard = new Scanner(System.in);
		int a,b;
		
		for(int i=0;i<40000;i++)
		{
			a=keyboard.nextInt();
			b=keyboard.nextInt();
			A.connect(a,b);
		}
		*/
		System.out.println(A.count());
		time2 = System.currentTimeMillis();
		System.out.println("花了：" + (time2-time1) /1000+ "秒");
	}
	int s[]=new int[2];
	int max=0;
	int l,l2;
	int h,h1,h2;
	int p,q;
	@Override
	public void connect(int a, int b) {
		// TODO Auto-generated method stub
		l=s.length;
		l2=s.length;
		if(a>max||b>max)
		{
			if(a>b)max=a;
			else max=b;
		}
		
		while(max>=l)
		{
			l=2*l;
		}
		if(l>l2) 
		{
			resize();
		}
		
		if(s[a]==0&&s[b]==0)
		{
				s[b]=b;
				s[a]=s[b];
			//System.out.print("1 ");
		}
		
		else if(s[a]==0&&s[b]!=0)
		{
			s[a]=find(b);
			//System.out.print("2 ");
		}
		else if(s[a]!=0&&s[b]==0)
		{
			s[b]=find(a);
			//System.out.print("3 ");
		}
		else
		{
			//System.out.print("4 ");
			if(s[a]!=s[b])
			{
				h=0;
				p=find(a);
				h1=h;
				h=0;
				q=find(b);
				h2=h;
				if(h1>h2)s[q]=p;
				else s[p]=q;
					
			}
		}
}

	private int find(int i)
	{
		
		while(i!=s[i])
		{
			s[i]=s[s[i]];
			i=s[i];
			h++;
		}
		return i;
	}

	private void resize()
	{
		int copy[]=new int[l];
		for(int i=1;i<l2;i++)
		{
			copy[i]=s[i];
		}
		s=copy;
	}
	@Override
	public int count() {
		// TODO Auto-generated method stub
		int c=0;
		/*System.out.println();
		for(int i=0;i<s.length;i++)
			System.out.print(i+"="+s[i]+" ");
		*/
		for(int i=1;i<=max;i++)
		{
			if(s[i]==i)c++;
		}
		return c;
	}

	
}


