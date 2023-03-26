from typing import List


def sum_non_neg_diag(x: List[List[int]]) -> int:
    summ = 0
    ind = 0
    for i in range(len(x)):
        if len(x[i])>i:
            if x[i][i] >= 0:
                summ += x[i][i]
                ind+=1
    if ind>0:
        return summ
    else:
        return -1
                     
            
    """
    Вернуть  сумму неотрицательных элементов на диагонали прямоугольной матрицы X. 
    Если неотрицательных элементов на диагонали нет, то вернуть -1
    """ 


def are_multisets_equal(x: List[int], y: List[int]) -> bool:
    if len(x) == len(y):
        xs = sorted(x)
        ys = sorted(y)
        for i in range(len(x)):
            if xs[i] != ys[i]:
                return False
        return True
    else:
        return False
    """
    Проверить, задают ли два вектора одно и то же мультимножество.
    """


def max_prod_mod_3(x: List[int]) -> int:
    maxpr = 0
    c = 0
    for i in range(1,len(x)):
        if x[i-1]*x[i] > maxpr and (x[i-1]%3 == 0 or x[i]%3 == 0):
            maxpr = x[i-1]*x[i]
            c +=1
    if c>0:
        return maxpr
    else:
        return -1
        
    """
    Вернуть максимальное прозведение соседних элементов в массиве x, 
    таких что хотя бы один множитель в произведении делится на 3.
    Если таких произведений нет, то вернуть -1.
    """


def convert_image(image: List[List[List[float]]], weights: List[float]) -> List[List[float]]:
    ch_sum = []
    
    for i in range(len(image)):
        ch = []
        for j in range(len(image[i])):
            s = sum([image[i][j][l] * weights[l] for l in range(len(weights))])
            ch.append(s)
        ch_sum.append(ch)
    #print(ch_sum)
    return ch_sum
    """
    Сложить каналы изображения с указанными весами.
    """

def rle_scalar(x: List[List[int]], y:  List[List[int]]) -> int:
    xvector = []
    for i in range(len(x)):
        for j in range(x[i][1]):
            xvector.append(x[i][0])
    yvector = []
    for i in range(len(y)):
        for j in range(y[i][1]):
            yvector.append(y[i][0])
    if (len(xvector) != len(yvector)):
        return -1
    else:
        scproduct = [xvector[i]*yvector[i] for i in range(len(xvector))]
        return sum(scproduct)
    """
    Найти скалярное произведение между векторами x и y, заданными в формате RLE.
    В случае несовпадения длин векторов вернуть -1.
    """


def cosine_distance(x: List[List[float]], y: List[List[float]]) -> List[List[float]]:
    mcosr = []
    for i in range(len(x)):
        vector = []
        for j in range(len(y)):
            cosinus = 0
            xs,ys,xys = 0,0,0
            for l in range(len(x[i])):
                xs += x[i][l]**2
                ys += y[j][l]**2
                xys += x[i][l] * y[j][l]
            if xs == 0 or ys == 0:
                cosinus = 1
            else:
                cosinus = (xys / ((xs * ys)**(1/2)))
            vector.append(cosinus)
        mcosr.append(vector)
    return mcosr
            
    """
    
    Вычислить матрицу косинусных расстояний между объектами X и Y. 
    В случае равенства хотя бы одно из двух векторов 0, косинусное расстояние считать равным 1.
    """