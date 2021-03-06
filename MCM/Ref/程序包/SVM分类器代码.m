
1.命令函数部分：

clear;%清屏
clc;
X =load('data.txt');
n = length(X);%总样本数量
y = X(:,4);%类别标志
X = X(:,1:3);
TOL = 0.0001;%精度要求
C = 1;%参数，对损失函数的权重
b = 0;%初始设置截距b
Wold = 0;%未更新a时的W(a)
Wnew = 0;%更新a后的W(a)
for i = 1 : 50%设置类别标志为1或者-1
    y(i) = -1;
end
a = zeros(n,1);%参数a
for i = 1 : n%随机初始化a,a属于[0,C]
        a(i) = 0.2;
end

%为简化计算，减少重复计算进行的计算
K = ones(n,n);
for i = 1 :n%求出K矩阵，便于之后的计算
    for j = 1 : n
        K(i,j) = k(X(i,:),X(j,:));
    end
end
sum = zeros(n,1);%中间变量，便于之后的计算，sum(k)=sigma a(i)*y(i)*K(k,i);
for k = 1 : n
    for i = 1 : n
        sum(k) = sum(k) + a(i) * y(i) * K(i,k);
    end
end

while 1%迭代过程
    
%启发式选点
n1 = 1;%初始化，n1,n2代表选择的2个点
n2 = 2;
%n1按照第一个违反KKT条件的点选择
while n1 <= n
    if y(n1) * (sum(n1) + b) == 1 && a(n1) >= C && a(n1) <=  0
         break;
    end
    if y(n1) * (sum(n1) + b) > 1 && a(n1) ~=  0
           break;
    end
    if y(n1) * (sum(n1) + b) < 1 && a(n1) ~=C
          break;
    end
     n1 = n1 + 1;              
end
%n2按照最大化|E1-E2|的原则选取
E1 = 0;
E2 = 0;
maxDiff = 0;%假设的最大误差
E1 = sum(n1) + b - y(n1);%n1的误差
for i = 1 : n
    tempSum = sum(i) + b - y(i);
    if abs(E1 - tempSum)> maxDiff
        maxDiff = abs(E1 - tempSum);
        n2 = i;
        E2 = tempSum;
    end
end

%以下进行更新
a1old = a(n1);
a2old = a(n2);
KK = K(n1,n1) + K(n2,n2) - 2*K(n1,n2);
a2new = a2old + y(n2) *(E1 - E2) / KK;%计算新的a2
%a2必须满足约束条件
S = y(n1) * y(n2);
if S == -1
    U = max(0,a2old - a1old);
    V = min(C,C - a1old + a2old);
else
    U = max(0,a1old + a2old - C);
    V = min(C,a1old + a2old);
end
if a2new > V
    a2new = V;
end
if a2new < U
    a2new = U;
end
a1new = a1old + S * (a2old - a2new);%计算新的a1
a(n1) = a1new;%更新a
a(n2) = a2new;

%更新部分值
sum = zeros(n,1);
for k = 1 : n
    for i = 1 : n
        sum(k) = sum(k) + a(i) * y(i) * K(i,k);
    end
end
Wold = Wnew;
Wnew = 0;%更新a后的W(a)
tempSum = 0;%临时变量
for i = 1 : n
    for j = 1 : n
    tempSum= tempSum + y(i )*y(j)*a(i)*a(j)*K(i,j);
    end
    Wnew= Wnew+ a(i);
end
Wnew= Wnew - 0.5 * tempSum;
%以下更新b：通过找到某一个支持向量来计算
support = 1;%支持向量坐标初始化
while abs(a(support))< 1e-4 && support <= n
    support = support + 1;
end
b = 1 / y(support) - sum(support);
%判断停止条件
if abs(Wnew/ Wold - 1 ) <= TOL
    break;
end
end
%输出结果：包括原分类，辨别函数计算结果，svm分类结果
for i = 1 : n
    fprintf('第%d点:原标号 ',i);
    if i <= 50
        fprintf('-1');
    else
        fprintf(' 1');
    end
    fprintf('    判别函数值%f      分类结果',sum(i) + b);
    if abs(sum(i) + b - 1) < 0.5
        fprintf('1\n');
    else if abs(sum(i) + b + 1) < 0.5
            fprintf('-1\n');
        else
            fprintf('归类错误\n');
        end
    end
end

2.名为f的功能函数部分:
function y = k(x1,x2)
    y = exp(-0.5*norm(x1 - x2).^2);
end

3.数据：
    0.8871   -0.3491    8.3376         0
    1.2519    1.2083    6.5041         0
   -1.1925    1.9338    1.8790         0
   -0.1277    2.4371    2.6971         0
    1.9697    3.0906    6.0391         0
    0.7603    0.8241    1.5323         0
    1.6382    3.5516    4.4694         0
    1.3438   -0.4539    5.9366         0
   -1.3361   -2.0201    1.6393         0
   -0.3886    3.3041    8.0450         0
   -0.6780    6.0196   -0.4084         0
    0.3552   -0.1051    1.2458         0
    1.6560    4.0786    0.8521         0
    0.8117    3.5451    6.8925         0
    1.4773   -1.9340    3.9256         0
   -0.0732   -0.9526    0.4609         0
    0.1521    4.3711    2.2600         0
    1.4820    0.7493    0.3475         0
    0.6140    4.5261    8.3776         0
    0.5721    3.3460    3.7853         0
    0.5269    4.1452    4.3900         0
    1.7879   -0.5390    2.5516         0
    0.9885    5.7625    0.1832         0
   -0.3318    2.4373   -0.6884         0
    1.3578    5.4709    3.4302         0
    2.7210   -1.1268    4.7719         0
    0.5039   -0.1025    2.3650         0
    1.1107    1.6885    3.7650         0
    0.7862    1.3587    7.3203         0
    1.0444   -1.5841    3.6349         0
    1.7795    1.7276    4.9847         0
    0.6710    1.4724   -0.5504         0
    0.2303    0.2720   -1.6028         0
    1.7089   -1.7399    4.8882         0
    1.0059    0.5557    5.1188         0
    2.3050    0.8545    2.8294         0
    1.9555    0.9898    0.3501         0
    1.7141    1.5413    3.8739         0
    2.2749    5.3280    4.9604         0
    1.6171    0.5270    3.3826         0
    3.6681   -1.8409    4.8934         0
    1.1964    1.8781    1.4146         0
    0.7788    2.1048    0.0380         0
    0.7916    5.0906    3.8513         0
    1.0807    1.8849    5.9766         0
    0.6340    2.6030    3.6940         0
    1.9069   -0.0609    7.4208         0
    1.6599    4.9409    8.1108         0
    1.3763    0.8899    3.9069         0
    0.8485    1.4688    6.7393         0
    3.6792    6.1092    4.9051         1
    4.3812    7.2148    6.1211         1
    4.3971    3.4139    7.7974         1
    5.0716    7.7253   10.5373         1
    5.3078    8.8138    6.1682         1
    4.1448    5.5156    2.8731         1
    5.3609    6.0458    4.0815         1
    4.7452    6.6352    1.3689         1
    6.0274    6.5397   -1.9120         1
    5.3174    3.0134    6.7935         1
    7.2459    3.6970    3.1246         1
    6.1007    8.1087    5.5568         1
    5.9924    6.9238    5.7938         1
    6.0263    5.3333    7.5185         1
    3.6470    8.0915    6.4713         1
    3.6543    7.2264    7.5783         1
    5.0114    6.5335    3.5229         1
    4.4348    7.4379   -0.0292         1
    3.6087    3.7351    3.0172         1
    3.5374    5.5354    7.6578         1
    6.0048    2.0691   10.4513         1
    3.1423    4.0003    5.4994         1
    3.4012    7.1536    8.3510         1
    5.5471    5.1372   -1.5090         1
    6.5089    5.4911    8.0468         1
    5.4583    6.7674    5.9353         1
    4.1727    2.9798    3.6027         1
    5.1672    8.4136    4.8621         1
    4.8808    3.5514    1.9953         1
    5.4938    4.1998    3.2440         1
    5.4542    5.8803    4.4269         1
    4.8743    3.9641    8.1417         1
    5.9762    6.7711    2.3816         1
    6.6945    7.2858    1.8942         1
    4.7301    5.7652    1.6608         1
    4.7084    5.3623    3.2596         1
    6.0408    3.3138    7.7876         1
    4.6024    8.3517    0.2193         1
    4.7054    6.6633   -0.3492         1
    4.7139    5.6362    6.2330         1
    4.0850   10.7118    3.3541         1
    6.1088    6.1635    4.2292         1
    4.9836    5.4042    6.7422         1
    6.1387    6.1949    2.5614         1
    6.0700    7.0373    3.3256         1
    5.6881    5.1363    9.9254         1
    7.2058    2.3570    4.7361         1
    4.2972    7.3245    4.7928         1
    4.7794    8.1235    3.1827         1
    3.9282    6.4092   -0.6339         1
