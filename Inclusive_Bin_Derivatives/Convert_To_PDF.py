import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.image as img

import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('-t', '--term', action='store',type=str,choices=['NPV',"Mu"], required=True, help='Term for pngs to convert to pdf')


if "__main__" == __name__:
    w = 10
    h = 10
    args = parser.parse_args()

    
    print(args.term)

    if args.term == "Mu":
        print("Opening Mu pngs")
        image0 = img.imread('./Dependence_Mu/Mu_pT_10_20_.png')
        image1 = img.imread('./Dependence_Mu/Mu_pT_20_30_.png')
        image2 = img.imread('./Dependence_Mu/Mu_pT_30_60_.png')
        image3 = img.imread('./Dependence_Mu/Mu_pT_60_120_.png')
        image4 = img.imread('./Dependence_Mu/Mu_pT_120_200_.png')
        image5 = img.imread('./Dependence_Mu/Mu_pT_10_200_.png')
        img_lst=[image0, image1, image2, image3, image4, image5]
        
    if args.term == "NPV":
        print("Opening NPV pngs")
        
        image0 = img.imread('./Dependence_NPV/NPV_pT_10_20_.png')
        image1 = img.imread('./Dependence_NPV/NPV_pT_20_30_.png')
        image2 = img.imread('./Dependence_NPV/NPV_pT_30_60_.png')
        image3 = img.imread('./Dependence_NPV/NPV_pT_60_120_.png')
        image4 = img.imread('./Dependence_NPV/NPV_pT_120_200_.png')            
        image5 = img.imread('./Dependence_NPV/NPV_pT_10_200_.png')
        img_lst=[image0, image1, image2, image3, image4, image5]

    fig = plt.figure(figsize=(20, 20),dpi=500)
    columns = 2
    rows = 3
    for i in range(1, columns*rows +1):
        
        fig.add_subplot(rows, columns, i)
        plt.imshow(img_lst[i-1],  interpolation="spline36")
        # spline36
    plt.savefig("./test"+args.term +".png")
