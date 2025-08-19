#pragma once

void FillRotationMatrix(double, double, double, double(*)[4]);
void FillTranslationMatrix(double, double, double, double(*)[4]);
void FillScaleMatrix(double, double, double, double(*)[4]);
void FillTransformMatrix(double, double, double, double, double, double, double, double(*)[4]);
void MatrixMultiplyM4(double(*)[4], double(*)[4], double(*)[4]);
void MatrixMultiplyV4(double(*)[4], double*, double*);
