//
//  Page2ViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 01/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class Page2ViewController: UIViewController {
    
    @IBAction func previousAction(_ sender: Any) {
        let storyBoard: UIStoryboard = UIStoryboard(name: "Tutorial", bundle: nil)
        let obj = storyBoard.instantiateViewController(withIdentifier: "Page1")
        
        let transition = CATransition()
        transition.duration = 0.5
        transition.type = CATransitionType.push
        transition.subtype = CATransitionSubtype.fromLeft
        transition.timingFunction = CAMediaTimingFunction(name:CAMediaTimingFunctionName.easeInEaseOut)
        view.window!.layer.add(transition, forKey: kCATransition)
        present(obj, animated: false, completion: nil)
    }
}
