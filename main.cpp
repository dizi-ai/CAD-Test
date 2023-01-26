#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <shapes.h>

// Random figures with random parameters
Figure* random_figure(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> figure_num(1,3);
    std::uniform_int_distribution<std::mt19937::result_type> radius(1,20);
    auto rad = radius(dev);
    if (figure_num(rng)  == 1){
        return new Circle(rad);
    }
    else if (figure_num(rng)  == 2){
        return new Ellipse(rad,rad);
    }
    std::uniform_int_distribution<std::mt19937::result_type> step(1,30);
    return new Helix(rad,step(rng));
}

int main(){
    std::vector<Figure*> all_objects;
    std::vector<Figure*> circles;
    double t = M_PI/4;
    double sum=0;
    
    // Populate a container (e.g. vector or list) of objects of these types created in random manner with random parameters.
    for (int i = 0; i < 20; i++){
        all_objects.push_back(random_figure());
    }

    //Print coordinates of points and derivatives of all curves in the container at t=PI/4.
    for (auto &i : all_objects){
        i->print(std::cout);
        auto points_xyz = i->GetPoints(t);
        std::cout << "Points at t=Pi/4: \n\tx:" << points_xyz.x << "\n\ty:"<< points_xyz.y << "\n\tz:" << points_xyz.z<< std::endl;
        auto derivative_xyz = i->derivative(t);
        std::cout << "Derivative at t=Pi/4: \n\tx:" << derivative_xyz.x << "\n\ty:"<< derivative_xyz.y << "\n\tz:" << derivative_xyz.z << std::endl; 
        // Populate a second container that would contain only circles from the first container.
        if (typeid(*i) == typeid(Circle)){
            circles.push_back(i);
        }
        std::cout<<std::endl;
    }

    

    // Implement computation of the total sum of radii using parallel computations
    #pragma omp parallel for 
    for (int i=0;i < circles.size(); ++i){
        sum += circles[i]->GetRadius();
    }

    // Sort the second container in the ascending order of circles’ radii.
    std::sort(circles.begin(), circles.end(), [](Figure* lh, Figure* rh){ return lh->GetRadius() < rh->GetRadius(); });
    for (auto &i : circles){
        std::cout << i->GetRadius() << std::endl;
    }
    std::cout << "sum of circles' radii: " << sum << std::endl;
    for (auto &i : all_objects){
        delete i;
    }
    return 0;
}