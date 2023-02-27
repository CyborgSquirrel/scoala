### FunctionalInterface

Un `FunctionalInterface` conține o singură metodă abstractă.

```java
@FunctionalInterface
interface ArithmeticExpression {
	double calculate(double a, double b);
}

class FormulaHelper {
	public static double patratBinom(double a, double b) {
		return Math.pow(a+b, 2);
	}
}

ArithmeticExpression ae = FormulaHelper::patratBinom;
```

### Funcții lambda

```java
@FunctionalInterface
interface Formula {
	double calculate(double x, double y);
}

Formula f = (double x, double y) -> {
	double z = x+y;
	return z*z;
};

Formula f1 = (double x, double y) -> { return Math.sqrt(x*x + y*y); };
Formula f2 = (x, y) -> { return Math.sqrt(x*x + y*y); };
Formula f3 = (x, y) -> Math.sqrt(x*x + y*y);
```
