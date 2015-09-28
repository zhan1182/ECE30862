public class Person {
   private String lastName;
   private String firstName;
   private String dob; // DD/MM/YYYY
   public String hello = "hello world";
   
   public Person(String ln, String fn, String fdob) {
      lastName = ln;
      firstName = fn;
      dob = fdob;
   }

   public String toString( ) {
     return firstName+" "+lastName+", born: "+dob;
   }

   public String getDOB( ) {
      return dob;
   }

   public String getFirstName( ) {
      return firstName;
   }

   public String getLastName( ) {
      return lastName;
   }
}
