# NAS(Network Architecture Search)

* **网络结构搜索**
  * 搜索算法的三大要素
    * 搜索空间（Search Space）
    * 搜索策略（Search Strategy）
    * 评估策略（Evaluation Strategy）

![image-20220527101823501](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527101823501.png)

* 搜索空间

  * 全局搜索空间（Global Search）

    * 空间极大，具有较大自由度，为了减少时间，给定模板（链式结构）

    * 搜索范围是每一个神经元，范围较大，不适宜设计较深的神经网络结构

  * 基于细胞的搜索空间（Cell-based Search Space）

    * ResNet，Alex-Net，固定的小范围的结构进行复制
    * NAS直接去组合细胞，大大降低搜索空间，提高搜索效率
    
    ![image-20220527103645955](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527103645955.png)
  
* 搜索算法优化（网络结构参数）

  * 强化学习
  
    * 时空差分方法
    * 策略梯度算法
    * 蒙特卡洛树搜索算法
  
    ![image-20220527103908623](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527103908623.png)
  
  * 进化算法（全局优化）
  
    * Mutation的确定
  
    ![image-20220527103921156](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527103921156.png)
  
  * 代理模型优化
  
    ![image-20220527104021314](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527104021314.png)
  
    * 上述两种算法的搜索复杂度较高，每次搜索出的网络都需要重新训练
    * 以历史数据作为数据的训练模型，对可能的评估结果进行估计
  
  * 一次性算法（One-shot Architecture Search）
  
    ![image-20220527104215267](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527104215267.png)
  
    * Joint Optimizing 联合优化过程
  
      * 权值共享：没有将每个网络的参数训练到收敛
  
      * 可微分的神经结构架构搜索（对内存的需求更大）
  
        ![image-20220527104341446](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527104341446.png)
  
      * 超网络
  
        ![image-20220527104450070](C:\Users\Lucid-X\AppData\Roaming\Typora\typora-user-images\image-20220527104450070.png) 

​		