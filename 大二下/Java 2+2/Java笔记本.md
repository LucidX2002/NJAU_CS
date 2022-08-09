# Java笔记本

## Chapter1 基础概念

### 1.1 JVM、JRE和JDK的区别

* **JVM(Java Virtual Machine)**：java虚拟机，用于保证java的跨平台的特性.（java语言是跨平台，jvm不是跨平台的）

* **JRE(Java Runtime Environment)**：java的运行环境,包括jvm+java的核心类库.

* **JDK(Java Development Kit)**：java的开发工具,包括jre+开发工具.



### 1.2 三种技术架构

* **JAVAEE(Java Platform Enterprise Edition) **，开发企业环境下的应用程序，主要针对web程序开发；

* **JAVASE(Java Platform Standard Edition)**，完成桌面应用程序的开发，是其它两者的基础；

* **JAVAME(Java Platform Micro Edition)**，开发电子消费产品和嵌入式设备，如手机中的程序.



## Chapter2 基础语法

### 2.1 变量

#### 2.1.1 变量分类

对象的状态是存储在字段里.

![image-20220401170842636](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220401170842636.png)



* **实例变量/非静态字段(Instance Variables/Non-Static Fields)**:从技术上讲，对象存储他们 的个人状态在“非静态字段”，也就是没有 static 关键字声明的字段。非静态字段也被称为 实例变量，因为它们的值对于类的每个实例来说是唯一的（换句话说，就是每个对象）; 自行车的当前速度独立于另一辆自行车的当前速度。 
* **类变量/静态字段(Class Variables/Static Fields)** ：类变量是用 static 修饰符声明的字段， 也就是告诉编译器无论类被实例化多少次，这个变量的存在，只有一个副本。特定种类 自行车的齿轮数目的字段可以被标记为``` static```，因为相同的齿轮数量将适用于所有情况。 代码 ```static int numGears = 6; ```将创建一个这样的静态字段。此外，关键字 ```final``` 也可以加入，以指示的齿轮的数量不会改变。 
* **局部变量(Local Variables)**：类似于对象存储状态在字段里，方法通常会存放临时状态在 局部变量里。语法与局部变量的声明类似（例如，``` int count = 0;``` ）。没有特殊的关键字来指定一个变量是否是局部变量，是由该变量声明的位置决定的。局部变量是类的方法中的变量。 
* **参数(Parameters)**：前文的例子中经常可以看到``` public static void main(String[] args)``` ，这里的 ```args``` 变量就是这个方法参数。要记住的重要一点是，参数都归类为“变量 （variable）”而不是“字段（field）”。

#### 2.1.2 变量命名

* 变量名称是**区分大小写**的。变量名可以是任何合法的标识符 - 无限长度的 Unicode字母和数字，以字母，美元符号 $ ，或下划线 _ 开头。推荐使用**字母开头**，**不鼓励用“_” “$”作为变量名开头**。**空格是不允许的**。 

* 随后的字符可以是字母，数字，美元符号，或下划线字符。惯例同样适用于这一规则。 **为变量命名，尽量是完整的单词**。名称不能是**关键字**或**保留字**。 

* 如果您选择的名称**只包含一个词，拼写单词全部小写字母**。如果它**由一个以上的单词， 每个后续单词的第一个字母大写**，如 ```gearRatio``` 和 ``currentGear``。如果你的变量存储一个 **恒定值**，使用 ```static final int NUM_GEARS = 6``` ，**每个字母大写**，并用**以下划线分隔后续字符**。按照惯例，下划线字符永远不会在其他地方使用。

#### 2.1.3 变量类型

Java 是静态类型（statically-typed）的语言，**必须先声明再使用**。基本数据类型之间不会共享状态。

| 数据类型 | 字段默认值 |
| :------: | :--------: |
|   byte   |     0      |
|  short   |     0      |
|   int    |     0      |
|   long   |     0L     |
|  float   |    0.0f    |
|  double  |    0.0d    |
|   char   |  '\u0000'  |
|  string  |    null    |
| boolean  |   false    |

**注意：**

* Java中**boolean类型和整型不能相互转换**
* Java不区分变量的声明与定义
* 对于局部变量如果可以通过变量的初始值推断出它的类型，就可以不用再声明类型，如：

```java
	var greeting = "hello"; // greeting is string
```

* **局部变量（Local Variable）**略有不同，编译器不会指定一个默认值未初始化的局部变量。访问一个未初 始化的局部变量会导致编译时错误。 

* **基本类型转换顺序**:``byte <（short=char）< int < long < float < double``

* **强制类型转换**: 高精度转化为低精度

  ```java 
  int a=257;
  byte b; 
  b = (byte)a;
  ```

### 2.2 数组（**Array**）

数组是一个容器对象，保存一个**固定数量**的**单一类型**的值。当数组**创建**时，数组的**长度就确定**了。创建后，其长度固定。

![image-20220401171918697](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220401171918697.png)

1. 声明数组

   声明数组的类型，如下： 

   ```java
   byte[] anArrayOfBytes; 
   short[] anArrayOfShorts; 
   long[] anArrayOfLongs; 
   float[] anArrayOfFloats; 
   double[] anArrayOfDoubles; 
   boolean[] anArrayOfBooleans; 
   char[] anArrayOfChars; 
   String[] anArrayOfStrings;
   ```

   也可以将中括号放数组名称后面（但不推荐）

   ```java
   float anArrayOfFloats[];//discouraged
   ```

2. 创建、初始化、访问数组

   简化创建初始化数组的方法。

   ```java
   int[] anArray = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
   ```

   数组里面可以声明数组，即**多维数组 （multidimensional array）**。

   ```java
   class MultiDimArrayDemo { 
       /*** @param args */ 
       public static void main(String[] args) { 
           String[][] names = { { "Mr. ", "Mrs. ", "Ms. " }, { "Smith", "Jones" } }; 
           // Mr. Smith 
           System.out.println(names[0][0] + names[1][0]); 
           // Ms. Jones 
           System.out.println(names[0][2] + names[1][1]);
       }
   }
   ```

   输出为： 

   ```java
   Mr. Smith 
   Ms. Jones
   ```

   可以通过**内建的 length 属性**来确认数组的大小

   ```java
   System.out.println(anArray.length);
   ```

3. 复制数组

   **System 类**有一个 **arraycopy** **方法**用于**数组的有效复制**：

   ```java
   public static void arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
   ```

   例如：

   ```java
   class ArrayCopyDemo { 
       /*** @param args */ 
       public static void main(String[] args) { 
           char[] copyFrom = { 'd', 'e', 'c', 'a', 'f', 'f', 'e', 'i', 'n', 'a', 't', 'e' , 'd' };
           char[] copyTo = new char[7]; 
           System.arraycopy(copyFrom, 2, copyTo, 0, 7); 
           System.out.println(new String(copyTo)); 
       } 
   }
   ```

   输出结果为

   ```
   caffein
   ```

4. 其他操作

   ```java
   class ArrayCopyOfDemo { 
   /*** @param args */ 
   	public static void main(String[] args) { 
   		char[] copyFrom = { 'd', 'e', 'c', 'a', 'f', 'f', 'e', 'i', 'n', 'a', 't', 'e' , 'd' };
       	char[] copyTo = java.util.Arrays.copyOfRange(copyFrom, 2, 9);
       	System.out.println(new String(copyTo)); 
       }
   }
   ```

* **binarySearch** ： 用于搜索 

* **equals** ： 比较两个数组是否相等 

* **fill** : 填充数组 

* **sort** : 数组排序，在 Java SE 8 以后，可以使用 **parallelSort** 方法，在多处理器系统的大数组并行排序比连续数组排序更快。



### 2.3 运算符

|  运算符  |        优先级         |
| :------: | :-------------------: |
|   后缀   |    expr++，expr--     |
| 一元运算 |                       |
|   乘法   |        \* / %         |
|   加法   |          + -          |
|   移位   |       << >> >>>       |
|   关系   | < > >= <= instance of |
|   相等   |         == !=         |
|    与    |           &           |
|   异或   |           ^           |
|    或    |           `           |
|  逻辑与  |                       |
|  逻辑或  |                       |
| 三元运算 |                       |
| 赋值运算 |                       |

####　2.3.1赋值运算符

＝是最常见的赋值运算符，可以用于对象的引用关联。

#### 2.3.2算数运算符

| 运算符 |           描述           |
| :----: | :----------------------: |
|   ＋   | 加法，也用于String的连接 |
|   －   |           减法           |
|   ＊   |           乘法           |
|   ／   |           除法           |
|   ％   |           求模           |

####



