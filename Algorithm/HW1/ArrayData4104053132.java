public class ArrayData4104053132 extends ArrayData{
	
	public static void main(String[] arg)
	{
		double[] testA={1.1,2.3,3};
		double[] testB={1,2,3.4};
		ArrayData4104053132 a= new ArrayData4104053132(testA);
		System.out.println(a.avg());
		System.out.println(a.max());
		System.out.println(a.inner_product(testB));
		a.reverse();
		for(int i=0;i<testA.length;i++) System.out.print(testA[i]+" ");
		System.out.println();
		a.shuffle();
		for(int i=0;i<testA.length;i++) System.out.print(testA[i]+" ");
		System.out.println();
		
		
	}
	
	public ArrayData4104053132(double[] A){
		this.A=A;
	}
	
	@Override
	public double max() {
		// TODO Auto-generated method stub
		double m=0;
		for(int i=0;i<A.length;i++)
		{
			if(A[i]>m)
			{
				m=A[i];
			}
		}
		return m;
	}

	@Override
	public double avg() {
		// TODO Auto-generated method stub
		double s=0;
		for(int i=0;i<A.length;i++)
		{
			s=s+A[i];
		}
		return s/A.length;
	}

	@Override
	public void reverse() {
		// TODO Auto-generated method stub
		//double[]
		double []temp=new double[A.length];
		for(int i=0;i<A.length;i++)
		{
			temp[A.length-1-i]=A[i];
		}
		for(int i=0;i<A.length;i++)
		{
			A[i]=temp[i];
		}
		
	}

	@Override
	public void shuffle() {
		// TODO Auto-generated method stub
		double temp=A[0];
		A[0]=A[1];
		A[1]=temp;
	}

	@Override
	public double inner_product(double[] B) {
		// TODO Auto-generated method stub
		double sum=0;
		for(int i=0;i<B.length;i++)
		{
			sum=sum+A[i]*B[i];
		}
		return sum;
	}
}
