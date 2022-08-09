# COST4133-JAVA程序设计线上模拟考试

## 一、选择题（20*2）

1. **JRE是指**

   Java Run Environment（Java运行环境）

2. **开发Java必须安装的软件**

   Java Development Kit（Java开发工具包）

3. **Java中，short占用的字节数目**

   2

4. **执行下列代码后，i，j的值分别是**

   ```java
   int i=1,j=10;
   do{
   	if(i++>--j)
   		continue;
   }while(i<5);
   System.out.println("i="+i+"j="+j);
   ```

   i=5;j=6

5. **下列程序的运行结果是**

   ```java
   public class Myclass{
   	private static int a = 100;
   	public static void modify(int a){
   		a+=5;
   	}
   	public static void main(String[] args){
   		modify(a);
   		System.out.println(a);
   	}
   }
   ```

   a=100,方法中执行的是形式参数，不是实际参数，对类中static int a没有任何影响。

## 二、程序阅读（3*5）

```java
TreeSet<String> mySet = new TreeSet<>();
mySet.add("one");
mySet.add("two");
mySet.add("three");
mySet.add("four");
mySet.add("one");
Iterator<String> it = new Iterator();
while(it.hasNext()){
	System.out.println(in.next()+" ");
}
```

**Ans: four one three two(Treeset按照字母序排列)**

## 三、编程题（3*15）

* 按照下列要求定义类和创建对象
  1. 定义一个名为**Rectangle的类表示矩形**，其中含有**length，width两个double类型的成员变量**表示矩形的长和宽。定义**求矩形周长的方法getPerimeter()**和**求面积的方法getArea()**；
  2. 定义一个**带参数构造方法**，通过**给出的长和宽**创建矩形对象。定义**默认构造方法**，在该方法中**调用有参数构造方法**,将矩形**长宽都设置为1.0**；
  3. 定义一个名为 **Cuboid的长方体类**，使其**继承Rectangle类**，其中包含一个**表示高的double型**成员变量height:定义一个**构造方法** Cuboid(double length, doublc width, double height);再定义一个求**长方体体积的volume()**方法；
  4. 编写测试类，测试以上程序。
  
  ```java
  class Rectangle {
      private double length,width;
      public Rectangle(double length,double width){
          this.length=length;
          this.width=width;
      }
      public Rectangle(){
          this(1,1);
      }
      public double getPerimeter(){
          return 2*(this.width+this.length);
      }
      public double getArea(){
          return this.length*this.width;
      }
  }
  
  class Cuboid extends Rectangle{
      double height;
      public Cuboid(double length, double width, double height){
          super(length,width);
          this.height=height;
      }
      public double volume(){
          double v = super.getArea();
          v*=height;
          return v;
      }
  }
  
  public class Test {
      public static void main(String[] args) {
          Rectangle rectangle1 = new Rectangle();
          System.out.println("Perimeter1: " + rectangle1.getPerimeter() );
          System.out.println("Area1: " + rectangle1.getArea() );
          Rectangle rectangle2 = new Rectangle(3,4);
          System.out.println("Perimeter2: " + rectangle2.getPerimeter() );
          System.out.println("Area2: " + rectangle2.getArea() );
          Cuboid cuboid = new Cuboid(3,4,5);
          System.out.println("Volume: "+cuboid.volume());
      }
  }
  ```
  
  



