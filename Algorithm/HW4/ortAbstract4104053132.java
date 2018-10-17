
public class SortAbstract4104053132 extends SortAbstract {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SortAbstract4104053132 A=new SortAbstract4104053132();
		int[] a = {800,32,67,382,66,31,75,49,324,56,10,30,24,300,23,45,67,87,98,12,34,56};
		show(A.MySort(a));
	}
	private static final int INSERTION_SORT_CUTOFF = 10;
	private int [] b;
	public int[] MySort(int[] x) {
		// TODO Auto-generated method stub
		 b = new int[x.length];
		 naturalMergeSort(x);
        //assert isSorted(x);
        
		return x;
	}
	private static void insertionSort(int[] a, int lo, int hi) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j-1]); j--)
                exch(a, j, j-1);
    }
	 private static boolean less(int v, int w) {
	        return compare(v,w) < 0;
	    }
	 private static int compare(int a,int b)
	    {
	    	return a-b;
	    }
	private static void exch(int[] a, int i, int j) {
        int swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

	private void  naturalMergeSort(int [] a) {
		 int left = 0;
	         int right = a.length - 1;
	         boolean sorted = false;
	         int l = 0;
	         int r = right;
	                   
	         do {
	        	 sorted = true;
		         left = 0;
		         
		
				     while (left < right) {
				    	 l = left;
				         while (l < right &&  a[l] <= a[l + 1]) {
				        	 l++;
				         }
				         r = l + 1;
				         while (r == right - 1 || r < right && a[r] <= a[r + 1]) {
				             r++;
				         }
				     
				         
				         if (r <= right) {
					         merge(a, left, l, r);
				             sorted = false;
			             }
			             left = r + 1;
	         }
			    	
		         } while (! sorted);
	         
			                    
		 }
			    
			            /**
			             * Merges the sorted sequence
			            *  a[links]...a[mitte] with a[mitte+1]..a[rechts]
			              *  into a sorted sequence
			            *  a[links] .. a[rechts].
			             */
		private void merge(int[] a, int left, int middle, int right) {
			int l = left;
			int r = middle + 1;
			   
			for (int i = left; i <= right; i++) {
				if (r > right || (l <= middle && a[l] <= a[r])) {
					b[i] = a[l++];
			    } 
				else if (l > middle || (r <= right && a[r] <= a[l])) {
			        b[i] = a[r++];
			    }
			}
			    
			for (int i = left; i <= right; i++) {
			    a[i] = b[i];
			}
		}
			        

	 private static void show(int[] a) {
	        for (int i = 0; i < a.length; i++) {
	            System.out.print(a[i]+" ");
	        }
	    }
	
	
}



/*

time1 = System.currentTimeMillis();
for(int t1=0;t1<size;t1++)
	for(int t2=0;t2<size;t2++)
		for(int t3=0;t3<size;t3++)
			asn[t1][t3]=asn[t1][t3]+Matrix.a[t1][t2]*Matrix.b[t2][t3];
 time2 = System.currentTimeMillis();
System.out.println("花了：" + (time2-time1)/1000 + "秒");
*/
