public class Student extends Person { // inherits from Person
   private String school;
   private String major;
   private double credits;
   private double totalPts;
//   private double gpa;

   public Student(String ln, String fn, String sch, String maj, String fdob, 
      double fcredits, double ftotalPts) {
      super(ln, fn, fdob);
      school = sch;
      major = maj;
      credits = fcredits;
      totalPts = ftotalPts;
//      gpa = totalPts/credits;
   }

   public String toString() {
      String s = "Student: "+getFirstName( )+" "+getLastName( )+", DOB: "+getDOB( );
      s = s+", School: "+school+", Major: "+getMajor( ); 
      return s+", credits: "+credits+", total points: "+totalPts+", major: "+major+", GPA: "+getGPA();
   }

   public String getSchool( ) {
	   return school;
   }

   public String getMajor( ) {
      return major;
   }

   public double getCredits( ) {
	   return credits;
   }

   public double getTotalPts( ) {
	   return totalPts;
   }

   public double getGPA( ) {
	   return totalPts/credits;
   }

   // can also have putGPA(), etc., if want to allow updates of fields.

   public String getDOB( ) {
      String dob = super.getDOB( );
      String month = dob.substring(0, 2);
      String day = dob.substring(3, 5);
      String year = dob.substring(6, 10);
      return day+"/"+month+"/"+year;
   }
}
