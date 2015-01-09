package jcpp.converter.model.expression;

import java.util.*;
import jcpp.converter.model.*;
import jcpp.converter.model.stmt.*;

//TODO not all fields can be filled, look at http://docs.oracle.com/javase/specs/jls/se7/html/jls-15.html#jls-15.10
public class CPPArrayCreationExpression extends CPPExpression{
    protected int arrayCount;
    protected List<CPPExpression> dimensions;
    protected CPPArrayInitializerExpression initializer;
    protected CPPType type;

	public CPPArrayCreationExpression(CPPMethod method){
        super(method);
        dimensions=new ArrayList<CPPExpression>();
	}

    public int getArrayCount(){
        return arrayCount;
    }

    public void setArrayCount(int i){
    	arrayCount=i;
    }

    public List<CPPExpression> getDimensions(){
        return dimensions;
    }

    public void addDimension(CPPExpression e){
        dimensions.add(e);
    }

    public CPPArrayInitializerExpression getInitializer(){
        return initializer;
    }

    public void setInitializer(CPPArrayInitializerExpression i){
        initializer=i;
    }

    public CPPType getType(){
        return type;
    }

    public void setType(CPPType t){
        type=t;
    }
}