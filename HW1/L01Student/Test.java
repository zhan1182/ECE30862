public class Test {

   public static void main(String[] args) {

      Person p1 = new Person("Johnson", "Tom", "10/13/1909");
      System.out.println(p1.hello);
      System.out.println(p1);
      Student s1 = new Student("Smith", "Mary", "Purdue", "ECE", 
                               "01/01/1994", 240.0, 800.0);
      System.out.println(s1);
      p1 = s1;
      System.out.println(p1);
      System.out.println(p1.getDOB( ));
//      System.out.println(p1.getGPA( ));
   }
}
