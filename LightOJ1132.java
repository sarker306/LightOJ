import java.math.BigInteger;
import java.util.Scanner;
/* MLE in LightOJ */
public class LightOJ1132 {
    private static BigInteger[] Sum;
    private static Scanner scn;
    private static int testCount;
    
    public static BigInteger SumOfPower( long n, int k ){
        if ( Sum[k] != BigInteger.ZERO ) return Sum[k];
        
        if ( k == 0 ) {
            return Sum[k] = BigInteger.valueOf(n);
        }
        else{
            BigInteger temp = BigInteger.valueOf(n+1).pow(k+1);
            for ( int i = 1 ; i <= k ; i++ ){
                temp = temp.subtract(Combination.nCk(k+1, i+1).multiply(SumOfPower(n, k-i)));
            }
            
            return Sum[k] = temp.subtract(BigInteger.ONE).divide(BigInteger.valueOf(k+1));
        }
    }
    
    static void ResetSum(){
        for ( int i = 0 ; i < Sum.length ; i++ ) Sum[i] = BigInteger.ZERO;
    }
    
    public static void main(String[] args) {
		BigInteger modulo = BigInteger.valueOf(1).shiftLeft(32);
		
        Combination.init();
        Sum = new BigInteger[55];
        
        scn = new Scanner(System.in);
        testCount = scn.nextInt();
        for ( int kase = 1 ; kase <= testCount ; kase++ ){
            long n = scn.nextLong();
            int k = scn.nextInt();
            ResetSum();
			System.out.print("Case " + kase + ": ");
            System.out.println(SumOfPower(n, k).mod(modulo));
        }
          
        scn.close();
    }
}

class Combination {
    static BigInteger[][] combination;
    
    public static void init(){
        combination = new BigInteger[55][];
        for ( int i = 0 ; i < combination.length ; i++ )
            combination[i] = new BigInteger[55];
    }
    
    public static BigInteger nCk( int n, int k ){
        BigInteger ans = new BigInteger("0");

        if ( n >= 0 && n < combination.length && k >= 0 && k < combination[n].length && combination[n][k] != null )
            return combination[n][k];
        if ( k > n ) return BigInteger.ZERO;
        if ( k == 0 ) return combination[n][k] = BigInteger.ONE;
        else ans = nCk( n - 1, k - 1 ).add( nCk ( n - 1, k ) );
        if ( n >= 0 && n < combination.length && k >= 0 && k < combination[n].length )
            combination[n][k] = ans;

        return ans;
    }
}
