//
//  Page1ViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 23/11/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import SwiftGifOrigin

class Page1ViewController: UIViewController {
    
    var delegate: AppWalkThroughDelegate!

    @IBOutlet weak var gifImage: UIImageView!
    
    override func viewDidLoad() {
        initView()
    }
    
    func initView() {
        gifImage.loadGif(name: "hm")
    }
    
    @IBAction func skipAction(_ sender: Any) {
//        UserDefaults.standard.set(true, forKey: "tutorial")
//        
////        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
////        
////        let newViewController = storyBoard.instantiateViewController(withIdentifier: "RootViewController") as! RootViewController
////        self.present(newViewController, animated: true, completion: nil)
//        
//        dismiss(animated: true, completion: nil)

    }
    
    @IBAction func nextAction(_ sender: Any) {
        let storyBoard: UIStoryboard = UIStoryboard(name: "Tutorial", bundle: nil)
        let obj = storyBoard.instantiateViewController(withIdentifier: "Page2")

        let transition = CATransition()
        transition.duration = 0.5
        transition.type = CATransitionType.push
        transition.subtype = CATransitionSubtype.fromRight
        transition.timingFunction = CAMediaTimingFunction(name:CAMediaTimingFunctionName.easeInEaseOut)
        view.window!.layer.add(transition, forKey: kCATransition)
        present(obj, animated: false, completion: nil)
    }
}
