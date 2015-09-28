public class Main {

   public static void main(String[] args) {

      B b = new B( );
      D1 d1 = new D1( );
      D2 d2 = new D2( );

      System.out.println("Base and b calls");
      B.f1( ); // The static method f1 in B is called.
      // B.f2( ); 
      b.f1( ); // The static method f1 in B is called.
      // b.f2( ); 
      b.f3( ); // The method f3 in B is called.
      // b.f4( ); 
      // b.f5( ); 
      b.bCaller( ); // The static methods f1, f2, f4 and method f3 in B are called.
      System.out.println(" ");

      System.out.println("D1 and d1 calls");
      D1.f1( ); // The static method f1 in D1 is called.
      // D1.f2( ); 
      d1.f1( ); // The static method f1 in D1 is called.
      // d1.f2( ); 
      d1.f3( ); // The method f3 in D1 is called.
      // d1.f4( ); 
      d1.f5( ); // The method f5 in D1 is called.
      // d1.f6( ); 
      // d1.f7( ); 
      d1.d1Caller( ); // The static method f1 and methods f3, f4, f5, f6 in D1 are called.
      System.out.println(" ");
     
      System.out.println("d1.bCaller");
      d1.bCaller( ); // The static methods f1, f2, f4 and method in B are called. The method f3 in D1 is called.
      System.out.println(" ");

      System.out.println("D2 and d2 calls");
      D2.f1( ); // The static method f1 in D2 is called.
      // D2.f2( ); 
      d2.f1( ); // The static method f2 in D2 is called.
      // d2.f2( ); 
      d2.f3( ); // The method f3 in D2 is called.
      // d2.f4( ); 
      d2.f5( ); // The method f5 in D2 is called.
      // d2.f6( ); 
      d2.f7( ); // The method f7 in D2 is called.
      d2.d2Caller( ); // The static methods f1, f4 and methods f3, f5, f7 in D2 are called.
      System.out.println(" ");
    }
}

