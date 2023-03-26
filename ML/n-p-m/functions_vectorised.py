import numpy as np


def sum_non_neg_diag(x: np.ndarray) -> int:
    d = np.diag(x)
    mask = d >= 0
    if len(d[mask]) == 0:
        return -1
    else:
        return sum(d[mask])
    """
    Вернуть  сумму неотрицательных элементов на диагонали прямоугольной матрицы X. 
    Если неотрицательных элементов на диагонали нет, то вернуть -1
    """


def are_multisets_equal(x: np.ndarray, y: np.ndarray) -> bool:
    return np.all(np.sort(x) == np.sort(y))
    """
    Проверить, задают ли два вектора одно и то же мультимножество.
    """


def max_prod_mod_3(x: np.ndarray) -> int:
    xnew = np.array(x[1:])
    xnew *= x[:-1]
    mask = xnew % 3 == 0
    if  len(xnew[mask]) == 0:
        return -1
    else:
        return max(xnew[mask])
    """
    Вернуть максимальное прозведение соседних элементов в массиве x, 
    таких что хотя бы один множитель в произведении делится на 3.
    Если таких произведений нет, то вернуть -1.
    """
    pass


def convert_image(image: np.ndarray, weights: np.ndarray) -> np.ndarray:
    return np.dot(image,weights)
    """
    Сложить каналы изображения с указанными весами.
    """
    pass


def rle_scalar(x: np.ndarray, y: np.ndarray) -> int:
    xvector = x.ravel()
    yvector = y.ravel()
    xvector1 = xvector[::2]
    xvector2 = xvector[1::2]
    xv = np.repeat(xvector1,xvector2)
    yvector1 = yvector[::2]
    yvector2 = yvector[1::2]
    yv = np.repeat(yvector1,yvector2)
    if len(xv)!=len(yv):
        return -1
    return np.sum(xv * yv)
    """
    Найти скалярное произведение между векторами x и y, заданными в формате RLE.
    В случае несовпадения длин векторов вернуть -1.
    """


def cosine_distance(x: np.ndarray, y: np.ndarray) -> np.ndarray:
    xy = np.dot(x,y.T)
    xnorm = np.linalg.norm(x, axis = 1, keepdims = True)
    ynorm = np.linalg.norm(y, axis = 1, keepdims = True)
    norm = xnorm * ynorm.T
    return np.where(norm == 0, 1, xy/norm)
    """
    Вычислить матрицу косинусных расстояний между объектами X и Y.
    В случае равенства хотя бы одно из двух векторов 0, косинусное расстояние считать равным 1.
    """
