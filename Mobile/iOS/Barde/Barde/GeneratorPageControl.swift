//
//  GeneratorPageControl.swift
//  Barde
//
//  Created by Arnaud Perrault on 08/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class GeneratorPageControl: UIPageControl {
    var activeImage: UIImage!
    var inactiveImage: UIImage!
    override var currentPage: Int {
        //willSet {
        didSet { //so updates will take place after page changed
            self.updateDots()
        }
    }
    
    convenience init(activeImage: UIImage, inactiveImage: UIImage) {
        self.init()
        
        self.activeImage = activeImage
        self.inactiveImage = inactiveImage
        
        self.pageIndicatorTintColor = UIColor.clearColor()
        self.currentPageIndicatorTintColor = UIColor.clearColor()
    }
    
    func updateDots() {
        for var i = 0; i < count(subviews); i++ {
            var view: UIView = subviews[i] as! UIView
            if count(view.subviews) == 0 {
                self.addImageViewOnDotView(view, imageSize: activeImage.size)
            }
            var imageView: UIImageView = view.subviews.first as! UIImageView
            imageView.image = self.currentPage == i ? activeImage : inactiveImage
        }
    }
    
    // MARK: - Private
    
    func addImageViewOnDotView(view: UIView, imageSize: CGSize) {
        var frame = view.frame
        frame.origin = CGPointZero
        frame.size = imageSize
        
        var imageView = UIImageView(frame: frame)
        imageView.contentMode = UIViewContentMode.Center
        view.addSubview(imageView)
    }
    
}
