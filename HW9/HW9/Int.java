import java.lang.Integer;

class Int implements Comparable {

    Integer i;
    
    public Int(int j) {i = new Integer(j);}
    
    // Implement the Comparable interface functions here.
    public double value(){
	return i.doubleValue();
    }
    
    public boolean lessThan(Comparable c){
	return this.value() < c.value();
    }

    public boolean equal(Comparable c){
	return this.value() ==  c.value();
    }

    public boolean greaterThan(Comparable c){
	return this.value() > c.value();
    }

}
