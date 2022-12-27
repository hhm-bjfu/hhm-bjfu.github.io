import random

q = p = 0
a = 0
XA = XB = 0
YA = YB = 0
KA = KB = 0

def Miller_Rabin(num): # 素性测试
    safeTime = 128
    s = num - 1
    t = 0
    while(s % 2 == 0):
        s >>= 1
        t = t + 1

    for trials in range(safeTime):
        random_a = random.randrange(2, num - 1)
        v = pow(random_a, s, num) # random_a ** s % num
        if v != 1:
            i = 0
            while v != (num - 1):
                if i == t - 1:
                    return False
                else:
                    i = i + 1
                    v = (v ** 2) % num
    return True

def is_Prime(num):
    # 小素数列表
    smallPrime=[
        2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,233,239,
        241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,
        421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,
        607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,
        809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997
        ]
    if(num < 2):
        return False

    if num in smallPrime: # 在表中
        return True

    for prime in smallPrime:
        if(num % prime == 0):
            return False

    return(Miller_Rabin(num))


def Output_Safeprime_p():
    p_min = 2 ** (1024 - 2)
    p_max = 2 ** (1024 - 1) - 1
    i = 0
    while True:
        p = random.randint(p_min, p_max)
        print(i)
        if (is_Prime(p) and is_Prime(2 * p + 1) == False): # 均不为素数
            print("--")
            return p
        else:
            i = i + 1

def FastExpMod(YB, XA, q):
    power = 1
    while XA:
        if XA & 1:
            power = (power * YB) % q
        XA >>= 1
        YB = (YB * YB) % q
    return power

def Generate_BenYuanGen(): # 生成本原根
    global p, q
    p = Output_Safeprime_p()
    q = p * 2 + 1
    while True: # 从最小值开始寻找本原根
        for g in range (2, q - 2): # 前闭后闭
            if(FastExpMod(g, 2, q) != 1 and FastExpMod(g, p, q) != 1
                return g

def RandomX(X): # 在范围内随机生成一个数
    X = random.randrange(2 ** (256 - 1), 2 ** (256))
    return X

def main(): # 主函数
    global a, XA, XB, YB, KA, KB
    a = Generate_BenYuanGen()
    print('q的本原根为: ', a)
    print('p的值为: ', p)
    print('q的值为: ', q)

    a = 3
    XA = RandomX(XA)
    XB = RandomX(XB)
    YA = FastExpMod(a, XA, q)
    print('YA的值为: ', YA)
    KA = FastExpMod(YA, XB, q)
    print('KA的值为: ', KA)
    YB = FastExpMod(a, XB, q)
    print('YB的值为: ', YB)
    KB = FastExpMod(YB, XA, q)
    print('KB的值为: ', KB)

if __name__ == '__main__':
    main()

