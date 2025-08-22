#include "hw1.h"

namespace algebra{

Matrix zeros(size_t n, size_t m){
    Matrix result(n, std::vector<double>(m));
    return result;
}

Matrix ones(size_t n, size_t m){
    Matrix result(n, std::vector<double> (m, 1.0));
    return result;

}

Matrix random(size_t n, size_t m, double min, double max){
    if(min >= max){
        throw std::logic_error("min must be smaller than max");
    }
    Matrix result(n, std::vector<double>(m));
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);

    for(auto& row:result){
        for(auto& number:row){
            number = dis(gen);
        }
    }

    return result;
}   

void show(const Matrix& matrix){
    for(const auto& row:matrix){
        for(const auto& element:row){
            std::cout << std::fixed << std::setprecision(3) << element << " ";
        }
        std::cout << std::endl;
    }
}

Matrix multiply(const Matrix& matrix, double c){
    Matrix result(matrix.size(), std::vector<double>(matrix[0].size()));

    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            result[i][j] = matrix[i][j] * c;
        }
    }

    return result;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.empty() || matrix2.empty()){
        return Matrix{};
    }
    if(matrix1[0].size() != matrix2.size()){
        throw std::logic_error("matrix1 column number must equals to matrix2 row number");
    }
    
    Matrix result(matrix1.size(), std::vector<double>(matrix2[0].size(), 0.0));

    for(size_t i = 0; i < matrix1.size(); i++){
        for(size_t j = 0; j < matrix2[0].size(); j++){
            for(size_t k = 0; k < matrix2.size(); k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

Matrix sum(const Matrix& matrix, double c){
    if(matrix.empty()){
        return Matrix{};
    }
    Matrix result(matrix.size(), std::vector<double>(matrix[0].size()));
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            result[i][j] = matrix[i][j] + c;
        }
    }
    return result;
}


Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.empty() && matrix2.empty()){
        return Matrix{};
    }
    else if(matrix1.empty() || matrix2.empty()){
        throw std::logic_error("error");
    }
    if(matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()){
        throw std::logic_error("shape must match");
    }

    Matrix result(matrix1.size(), std::vector<double>(matrix1[0].size()));
    for(size_t i = 0; i < matrix1.size(); i++){
        for(size_t j = 0; j < matrix1[0].size(); j++){
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

Matrix transpose(const Matrix& matrix){
    if(matrix.empty()){
        return Matrix{};
    }
    Matrix result(matrix[0].size(), std::vector<double>(matrix.size()));
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[0].size(); j++){
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m){
    if(matrix.empty()){
        return Matrix{};
    }
    Matrix result(matrix.size()-1, std::vector<double>(matrix[0].size()-1));

    size_t row = 0;
    for(size_t i = 0; i < matrix.size(); i++){
        if(i == n) continue;
        size_t column = 0;
        for(size_t j = 0; j < matrix[0].size(); j++){
            if(j == m) continue;
            result[row][column] = matrix[i][j];
            column++;
        }
        row++;
    }

    return result;
}

double determinant(const Matrix& matrix){
    if(matrix.empty()) return 1;
    if(matrix.size() != matrix[0].size()){
        throw std::logic_error("rows doesn't match the column");
    }
    if(matrix.size() == 1) return matrix[0][0];
    else if(matrix.size() == 2){
        double result;
        result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        return result;
    }
    double result = 0.0;
    int factor = 1;
    for(size_t i = 0; i < matrix.size(); i++){
        result += matrix[0][i] * factor * determinant(minor(matrix, 0, i));
        factor *= -1;
    }
    return result;
}

Matrix inverse(const Matrix& matrix){
    if(matrix.empty()) return Matrix{};
    if(matrix.size() != matrix[0].size()){
        throw std::logic_error("Matrix must be square");
    }

    double det = determinant(matrix);
    if(det == 0){
        throw std::logic_error("matrix is singular");
    }
    Matrix result(matrix.size(), std::vector<double> (matrix.size()));
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix.size(); j++){
            int factor = (i + j) % 2 ? -1 : 1;
            result[j][i] = factor * determinant(minor(matrix, i, j));
        }
    }
    return multiply(result, 1/det);
}

Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
    if(matrix1.empty() && matrix2.empty()){
        return Matrix{};
    }
    else if(matrix1.empty() || matrix2.empty()){
        throw std::logic_error("error");
    }

    if(axis == 0 && (matrix1[0].size() != matrix2[0].size())){
        throw std::logic_error("column number must match");
    }
    if(axis == 1 && (matrix1.size() != matrix2.size())){
        throw std::logic_error("row number must match");
    }
    if(axis == 0){
        Matrix result(matrix1.size() + matrix2.size(), std::vector<double>(matrix1[0].size()));
        for(size_t i = 0; i < matrix1[0].size(); i++){
            for(size_t j = 0; j < matrix1.size(); j++){
                result[j][i] = matrix1[j][i];
            }
            for(size_t j = 0; j < matrix2.size(); j++){
                result[j + matrix1.size()][i] = matrix2[j][i];
            }
        }
        return result;
    }
    else{
        Matrix result(matrix1.size(), std::vector<double>(matrix1[0].size() + matrix2[0].size()));
        for(size_t i = 0; i < matrix1.size(); i++){
            for(size_t j = 0; j < matrix1[0].size(); j++){
                result[i][j] = matrix1[i][j];
            }
            for(size_t j = 0; j < matrix2[0].size(); j++){
                result[i][j + matrix1[0].size()] = matrix2[i][j];
            }
        }
        return result;
    }
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
    if(matrix.empty()){
        return Matrix{};
    }
    if(r1 >= matrix.size() || r2 >= matrix.size()){
        throw std::logic_error("exceed matrix");
    }

    if(r1 == r2){
        return matrix;
    }

    Matrix result = matrix;
    for(size_t i = 0; i < result[0].size(); i++){
        double temp = result[r2][i];
        result[r2][i] = result[r1][i];
        result[r1][i] = temp;
    }
    return result;
}
Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
    if(matrix.empty()){
        return Matrix{};
    }

    Matrix result = matrix;
    for(size_t i = 0; i < result[0].size(); i++){
        result[r][i] *= c;
    }
    return result;
}
Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
    if(matrix.empty()){
        return Matrix{};
    }

    Matrix result = matrix;
    for(size_t i = 0; i < result[0].size(); i++){
        result[r2][i] += result[r1][i] * c;
    }
    return result;
}

Matrix upper_triangular(const Matrix& matrix){
    if(matrix.empty()){
        return Matrix{};
    }
    if(matrix.size() != matrix[0].size()){
        throw std::logic_error("rows should equal to column");
    }

    Matrix result = matrix;
    for(size_t i = 0; i < matrix.size()-1; i++){
        for(size_t j = i+1; j < matrix.size(); j++){
            double factor = result[j][i] / result[i][i];
            result = ero_sum(result, i, -1 * factor, j);
        }
    }
    return result;
}

}