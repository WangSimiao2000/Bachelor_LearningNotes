## Unity Shader的顶点/片元着色器的基本结构

```c
Shader "Custom/ShaderName"
{
    Properties
    {
        // 属性
    }

    SubShader
    {
        // 针对显卡A的SubShader
        Pass
        {
            // 设置渲染状态和标签

            // 开始CG代码片段
            CGPROGRAM
            // 该代码片段的编译指令, 例如:
            #pragma vertex vert
            #pragma fragment frag
            
            ENDCG

            // 其他设置
        }
        // 其他需要的Pass
    }
    SubShader
    {
        // 针对显卡B的SubShader
    }

    // 上述SubShader都失败后用于回调的Unity Shader
    FallBack "VertexLit"
}
```

## 一个简单的Shader例子

```c
Shader "Unity Shader Book/Chapter 5/Simple Shader" {   
    SubShader {       
        Pass {
            CGPROGRAM
            
            #pragma vertex vert
            #pragma fragment frag
            
            float4 vert(float4 v : POSITION) : SV_POSITION {
				return UnityObjectToClipPos (v);
			}

            fixed4 frag() : SV_Target {
                return fixed4(1.0, 1.0, 1.0, 1.0);
            }

            ENDCG
        }
    }
}
```

```c
Shader "Unity Shader Book/Chapter 5/Simple Shader"
```

以上代码定义了Shader的名字, 良好的命名规范可以让我们更好的管理Shader.

在CGPROGRAM和ENDCG之间的代码是CG代码片段:

```c
#pragma vertex name1
#pragma fragment name2
```

这两行指令告诉Unity编译器, 其中name1和name2就是我们指定的函数名

```c
float4 vert(float4 v : POSITION) : SV_POSITION {
	return mul (UNITY_MATRIX_MVP, v);
}
```

这里的vert函数是顶点着色器, 用于计算顶点的位置, 传入的参数是顶点的位置, 返回值是顶点在裁剪空间的位置. 

POSITION和SV_POSITION都是CG/HLSL的内置语义
- POSITION表示把模型的顶点坐标输入到参数v中
- SV_POSITION表示输出的是顶点在裁剪空间的顶点坐标

UNITY_MATRIX_MVP是一个内置的变量, 表示Model-View-Projection矩阵, 用于将顶点从模型空间转换到裁剪空间

注意, 现在的Unity版本已经不再推荐使用mul函数, 而是使用UnityObjectToClipPos函数:

```c
float4 vert(float4 v : POSITION) : SV_POSITION {
	return UnityObjectToClipPos (v);
}
```

```C
fixed4 frag() : SV_Target {
    return fixed4(1.0, 1.0, 1.0, 1.0);
}
```

frag函数没有任何输入, 输出是一个fixed4类型的变量, 使用了SV_Target语义进行限定
- SV_Target告诉渲染器, 把用户的输出颜色存储到一个渲染目标(render target)中

## 模型数据从哪里来

要想得到模型上每个顶点的纹理坐标和法线方向, 我们需要使用纹理坐标来访问纹理, 使用法线方向来计算光照效果. 因此, 我们需要为顶点着色器定义一个新的输入参数, 而不再是一个简单的数据类型, 而是一个结构体:

```c
Shader "Unity Shader Book/Chapter 5/Simple Shader" {   
    SubShader {       
        Pass {
            CGPROGRAM
            
            #pragma vertex vert
            #pragma fragment frag
            
            // 使用一个结构体来定义顶点着色器的输入
            struct a2v {
                // POSITION语义告诉Unity, 用模型空间的顶点坐标填充vertex变量
                float4 vertex : POSITION;
                // NORMAL语义告诉Unity, 用模型空间的法线坐标填充normal变量
                float3 normal : NORMAL;
                // TEXCOORD0语义告诉Unity, 用模型的第一套纹理坐标填充texcoord变量
                float4 texcoord : TEXCOORD0;
            };

            float4 vert(a2v v) : SV_POSITION {
                // 使用v.vertex来访问模型空间的顶点坐标
				return UnityObjectToClipPos (v.vertex);
			}

            fixed4 frag() : SV_Target {
                return fixed4(1.0, 1.0, 1.0, 1.0);
            }

            ENDCG
        }
    }
}
```

为了创建一个自定义的结构体, 必须使用以下格式来定义:

```c
struct StructName {
    Type Name : Semantic;
    Type Name : Semantic;
};
```
- 其中, 语义是不可被省略的
- 然后我们修改了vert函数的参数, 使其接受一个a2v类型的结构体作为输入参数
- a2v中a表示应用(Application), v表示顶点着色器(Vertex Shader), a2v表示把数据从应用阶段传递到顶点着色器阶段

## 顶点着色器与片元着色器的数据传递

```c
Shader "Unity Shader Book/Chapter 5/Simple Shader" {   
    SubShader {       
        Pass {
            CGPROGRAM
            
            #pragma vertex vert
            #pragma fragment frag
            
            // 使用一个结构体来定义顶点着色器的输入
            struct a2v {
                // POSITION语义告诉Unity, 用模型空间的顶点坐标填充vertex变量
                float4 vertex : POSITION;
                // NORMAL语义告诉Unity, 用模型空间的法线坐标填充normal变量
                float3 normal : NORMAL;
                // TEXCOORD0语义告诉Unity, 用模型的第一套纹理坐标填充texcoord变量
                float4 texcoord : TEXCOORD0;
            };

            // 使用一个结构体来定义顶点着色器的输出
            struct v2f {
                // SV_POSITION语义告诉Unity, 用裁剪空间的顶点坐标填充pos变量
                float4 pos : SV_POSITION;
                // COLOR0语义告诉Unity, 用颜色填充color变量
                float3 color : COLOR0;
            };

            v2f vert(a2v v) {
                // 使用v.vertex来访问模型空间的顶点坐标
				// return UnityObjectToClipPos (v.vertex);

                // 声明输出结构
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);
                // v.normal是模型空间的法线坐标, 其分量范围在(-1.0, 1.0)之间
                // 下面的代码将其转换到(0.0, 1.0)之间
                // 储存到o.color中, 传递给片元着色器
                o.color = v.normal * 0.5 + fixed3(0.5, 0.5, 0.5);
                return o;
			}

            fixed4 frag(v2f i) : SV_Target {
                //return fixed4(1.0, 1.0, 1.0, 1.0);

                // 将插值后的i.color显示到屏幕上
                return fixed4(i.color, 1.0);
            }

            ENDCG
        }
    }
}
```

- 这里与《Unity Shader 入门精要》中不同的是, 修改后顶点着色器不需要加上语义SV_POSITION(书上的例子是v2f vert(a2v v) : SV_POSITION), 因为实际使用中, 加上后会报错, (Unity 2022.3.42f1)
- COLOR0里可以储存任意信息, 由用户自定义, 但是一般用来储存顶点的颜色信息, 例如漫反射颜色, 逐顶点高光反射颜色等

## 如何使用属性

材质提供了一个可以方便地调节Unity Shader中参数的方式, 这些参数需要写在Properties块(属性块)中:
    
```c
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shader Book/Chapter 5/Simple Shader" {
    Properties {
        // 声明一个Color类型的属性, 名称为"Color Tint", 默认值为(1.0, 1.0, 1.0, 1.0), _Color是属性在着色器中的名字
        _Color ("Color Tint", Color) = (1.0,1.0,1.0,1.0)
    }
    SubShader {       
        Pass {
            CGPROGRAM
            
            #pragma vertex vert
            #pragma fragment frag

            // 在CG代码块中, 我们需要定义一个与属性名称和类型相同的变量, 用于在着色器中访问属性
            fixed4 _Color;
            
            // 使用一个结构体来定义顶点着色器的输入
            struct a2v {
                // POSITION语义告诉Unity, 用模型空间的顶点坐标填充vertex变量
                float4 vertex : POSITION;
                // NORMAL语义告诉Unity, 用模型空间的法线坐标填充normal变量
                float3 normal : NORMAL;
                // TEXCOORD0语义告诉Unity, 用模型的第一套纹理坐标填充texcoord变量
                float4 texcoord : TEXCOORD0;
            };

            // 使用一个结构体来定义顶点着色器的输出
            struct v2f {
                // SV_POSITION语义告诉Unity, 用裁剪空间的顶点坐标填充pos变量
                float4 pos : SV_POSITION;
                // COLOR0语义告诉Unity, 用颜色填充color变量
                float3 color : COLOR0;
            };

            v2f vert(a2v v) {
                // 使用v.vertex来访问模型空间的顶点坐标
				// return UnityObjectToClipPos (v.vertex);

                // 声明输出结构
                v2f o;
                o.pos = UnityObjectToClipPos (v.vertex);
                // v.normal是模型空间的法线坐标, 其分量范围在(-1.0, 1.0)之间
                // 下面的代码将其转换到(0.0, 1.0)之间
                // 储存到o.color中, 传递给片元着色器
                o.color = v.normal * 0.5 + fixed3(0.5, 0.5, 0.5);
                return o;
			}

            fixed4 frag(v2f i) : SV_Target {
                //return fixed4(1.0, 1.0, 1.0, 1.0);

                // 将插值后的i.color显示到屏幕上
                // return fixed4(i.color, 1.0);

                fixed3 c = i.color;
                // 使用_Color属性的值来调整颜色
                c *= _Color.rgb;
                return fixed4(c, 1.0);
            }

            ENDCG
        }
    }
}
```

- 添加Properties块, 用于声明属性
- 属性的格式为: `属性名(显示在Inspector中的名字, 类型) = (默认值)`
- 在CG代码块中, 我们需要定义一个与属性名称和类型相同的变量, 用于在着色器中访问属性

## Unity 提供的内置文件和变量

### 内置的包含文件

包含文件(include file)是类似C++中的头文件, 用于包含一些常用的函数和变量, 我们可以使用#include指令来包含这个文件:

```c
CGPROGRAM
// ...
#include "UnityCG.cginc"
// ...
ENDCG
```

| 文件名 | 描述 |
| --- | --- |
| UnityCG.cginc | 包含了最常用的帮助函数, 宏和结构体等 |
| UnityShaderVariables.cginc | 在编译Unity Shader时, 会被自动包含, 包含了许多内置的全局变量, 例如UNITY_MATRIX_MVP等 |
| Lighting.cginc | 包含了各种内置的光照模型, 如果编写的时Surface Shader的话会被自动包含 |
| HLSLSupport.cginc | 在编译Unity Shader时, 会被自动包含, 声明了很多用于跨平台遍历的宏和定义 |

UnityCG.cginc文件中包含了许多有用的结构体, 为我们的编写Shader提供了很多便利

| 名称 | 描述 | 包含的变量 |
| --- | --- | --- |
| appdata_base | 用于定义顶点着色器输入 | 顶点位置, 顶点法线, 第一组纹理坐标 |
| appdata_tan | 用于定义顶点着色器输入 | 顶点位置, 顶点切线, 顶点法线, 第一组纹理坐标 |
| appdata_full | 用于定义顶点着色器输入 | 顶点位置, 顶点切线, 顶点法线, 四组(或更多)纹理坐标 |
| appdata_img | 用于定义顶点着色器输入 | 顶点位置, 第一组纹理坐标 |
| v2f_img | 用于定义顶点着色器输出 | 裁剪空间中的顶点位置, 纹理坐标 |

UnityCG.cginc文件中也包含了许多有用的函数

| 函数名 | 描述 |
| --- | --- |
| float3 WorldSpaceViewDir(float4 v) | 输入一个*模型空间*中的顶点位置, 返回*世界空间*中该点到相机的观察方向 |
| float3 ObjSpaceViewDir(float4 v) | 输入一个*模型空间*中的顶点位置, 返回*模型空间*中该点到相机的观察方向 |
| float3 WorldSpaceLightDir(float4 v) | 仅用于前向渲染中. 输入一个*模型空间*的顶点位置, 返回*世界空间*中该点到光源的光照方向, 没有归一化 |
| float3 ObjSpaceLightDir(float4 v) | 仅用于前向渲染中. 输入一个*模型空间*的顶点位置, 返回*模型空间*中该点到光源的光照方向, 没有归一化 |
| float3 UnityObjectToWorldNormal(float3 n) | 输入一个*模型空间*中的法线, 返回*世界空间*中的法线 |
| float3 UnityObjectToWorldDir(float3 n) | 输入一个*模型空间*中的方向, 返回*世界空间*中的方向 |
| float3 UnityWorldToObjectDir(float3 n) | 输入一个*世界空间*中的方向, 返回*模型空间*中的方向 |

### Unity 支持的语义

#### 应用阶段传递给顶点着色器的常用语义

| 语义 | 描述 |
| --- | --- |
| POSITION | 模型空间中顶点的位置, 通常是float4类型 |
| NORMAL | 模型空间中顶点的法线方向, 通常是float3类型 |
| TANGENT | 模型空间中顶点的切线方向, 通常是float3类型 |
| TEXCOORD0 | 模型的第一套纹理坐标, 通常是float4类型 |
| TEXCOORD1 | 模型的第二套纹理坐标, 通常是float4类型 |
| TEXCOORDn | 模型的第n+1套纹理坐标, 通常是float4类型 |
| COLOR | 顶点的颜色, 通常是fixed4或float4类型 |

TEXCOORD n 中的n的数目和 Shader Model 有关, 例如 Shader Model 2.0/3.0 支持最多8个纹理坐标, Shader Model 4.0/5.0 支持最多16个纹理坐标

#### 顶点着色器传递给片元着色器的常用语义

| 语义 | 描述 |
| --- | --- |
| SV_POSITION | 顶点在裁剪空间的位置, 结构体中必须包含一个用该语义修饰的变量, 等同于Direct9中的POSITION, 但最好使用SV_POSITION |
| COLOR0 | 通常用于输出第一组顶点颜色, 但不是必须的 |
| COLOR1 | 通常用于输出第二组顶点颜色, 但不是必须的 |
| TEXCOORD0~TEXCOORD7 | 通常用于输出纹理坐标, 但不是必须的 |

上述语义中, SV_POSITION是有特别含义的, 其他的语义可以根据需要来定义变量的含义, 也就是说, 我们可以存储任意值到这些语义描述变量中
- 如果我们需要把一些自定义的数据从顶点着色器传递给片元着色器, 可以使用TEXCOORD0语义: `float4 texcoord : TEXCOORD0;`

#### 片元着色器输出的常用语义

| 语义 | 描述 |
| --- | --- |
| SV_Target | 输出值会存储到渲染目标中, 等同于Direct9中的COLOR, 但最好使用SV_Target |

