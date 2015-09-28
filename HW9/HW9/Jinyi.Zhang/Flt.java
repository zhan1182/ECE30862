import java.lang.Float;

class Flt implements Comparable {

    Float f; // the value returned by the value method.
    
    public Flt(float f) {this.f = new Float(f);}
    
    public double value(){
	return f.doubleValue();
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
