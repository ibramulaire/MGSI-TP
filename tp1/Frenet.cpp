#include "Frenet.h"

Frenet::Frenet(double rayon):RayonExtrusion(rayon){

}
Frenet::~Frenet(){


}


    std::vector<Sommet>&Frenet::getvecTangent() {

    return vecTangent;

    }
    std::vector<Sommet>& Frenet::getvecNormale() {
        return vecNormale;
    }
    std::vector<Sommet>&Frenet::getVecOxulateur() {
        return VecOxulateur;
    } 


    std::vector<Cercle>&Frenet::getCercles(){
        return cercles;
    }

    std::vector<Cercle>&Frenet::getCerclesBalayant()
    {
        return CerclesBalayant;
    }


    void Frenet::setRayonExtrusion(double rayon)
    {
      RayonExtrusion=rayon;
        
    }
    void Frenet::TousCalculer(Courbes c)
    {
         std::vector<Sommet>& tangente=c.getDerivations();
         std::vector<Sommet>& Secondderiver=c.getSecondDerivations();
         std::vector<Sommet>& curve=c.getCurveVertices();
         for (int i(0); i <c.getNbVertex() ; i++)
         {
           vecTangent.push_back(tangente[i].Normalise(1));
           vecNormale.push_back((Secondderiver[i].Moins((tangente[i].Normalise(2)).Foi(tangente[i].ProduitScalaire(Secondderiver[i])))).Normalise(1));
           VecOxulateur.push_back((vecTangent[i].ProduitVectoriele(vecNormale[i])).Normalise(1));
        
           double rayon=(tangente[i].getNorme(3))/(tangente[i].ProduitVectoriele(Secondderiver[i])).getNorme(1);
           Sommet centre=curve[i].Plus( (vecNormale[i].Foi(rayon)));
           std::vector<Sommet>PointCercles;
           std::vector<Sommet>PointCerclesextrud;
           int n=c.getNbVertex();
           for(int j=0;j<n;j++)
           {
             PointCercles.push_back(centre.Plus((vecNormale[i].Foi(cos((j*2*3.14)/n)).Plus(vecTangent[i].Foi(sin((j*2*3.14)/n)))).Foi(rayon)));
             PointCerclesextrud.push_back(curve[i].Plus((vecNormale[i].Foi(cos((j*2*3.14)/n)).Plus(VecOxulateur[i].Foi(sin((j*2*3.14)/n)))).Foi(this->RayonExtrusion)));


           }
           cercles.push_back({centre,rayon,PointCercles});
           CerclesBalayant.push_back({curve[i],this->RayonExtrusion,PointCerclesextrud});
         }
         



    }