import java.util.Scanner;
class Exe
{ 
    public static void main(String args[])
    {
      Scanner ob=new Scanner(System.in);
      System.out.print("n------------------n!!    ENTER THE NO.  !!  : ");
    double n=ob.nextDouble();
    System.out.println("n ---------------------------------------------");
    dixon(n);
    }
    public static double  gcd(double a,double b)
    {
        if(b==0)
        return a;
        else if(b>a)
        return gcd(b,a);
        else
        return gcd(b,a%b);
    }
  
    public static int  checkprime(double n)
    {
    int f=0;
      for(int i=2;i<=n/2;i++)
      {
        if(n%i==0)
        {
            f=1;
            break;
        }
              }
             if(f==1)
    return 0;
       else
    return 1;
    }
    public static void dixon(double n)
    {  
        int a,d,b1,d1;
        double m,x,p,q;
        m=Math.sqrt(n);
        double c=Math.floor(m);
        int f1=0;
        for(double f=c+1;f<=n;f++)
        {
            double s,m1;
            s=Math.sqrt((f*f)%n);
            m1=Math.floor(s);
            if((s-m1)==0)
            {
                if(s!=(f%n))
                {
                p=f+s;
                q=f-s;
                b1=checkprime(p);
                d1=checkprime(q);
                if(b1==1)
                {
                double z=gcd(q,n);
                int b=checkprime(z);
                if(b==1){
                System.out.println(" -----------------------------------------------------");
                System.out.println("  THE TWO FACTORS ARE    "+z+"  and    "+p);
                System.out.println(" ------------------------------------------------------");
              
                }
                }
                else if(d1==1)
                {
                double z=gcd(p,n);
                int b=checkprime(z);
                if(b==1){
                System.out.println("---------------------------------------------");
                System.out.println("    THE TWO FACTORS ARE     "+z+"       and    "+q);
                System.out.println("---------------------------------------------");}
                }
                else
                System.out.println("--------------- NEITHER OF THE FACTORS ARE PRIME---------" );    
                f1=1;
                break;
                }
            }
                if(f1==1)
                break;  
        }
    }          
}