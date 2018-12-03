//
//  BatteryViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 03/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.

import Foundation
import UIKit

class BatteryViewController: UIViewController {
    
    @IBOutlet weak var styleScrollView: UIScrollView!
    
    var styleSelected: String! = ""
    
    var buttons: [CheckButton] = []
    var styleArray: [String] = []
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        let styles = ["Activer"]
        let x = 8
        var y = 0
        
        
        styles.forEach{style in
            y += 50
            
            let button = CheckButton(frame: CGRect(x: Int(x), y: y, width: 300, height: 30))
            button.layer.borderColor = UIColor.white.cgColor
            button.setTitle(style, for: [])
            
            button.layer.cornerRadius = 6
            button.layer.borderWidth = 2.0
            
            button.center.x = self.view.center.x;
            
            self.styleScrollView.addSubview(button)
            
            
            button.widthAnchor.constraint(equalTo: styleScrollView.widthAnchor, constant: 0).isActive = true
            button.trailingAnchor.constraint(equalTo: styleScrollView.trailingAnchor, constant: 20).isActive = true
            button.leadingAnchor.constraint(equalTo: styleScrollView.leadingAnchor, constant: 20).isActive = true
            
            button.addTarget(self, action: #selector(buttonAction(_:)), for: .touchUpInside)
            
        }
        
    }
    
    @objc func buttonAction(_ sender: CheckButton) {
//        buttons.append(sender)
//
//        print(buttons)
//        buttons.forEach { (button) in
//            if (button.titleLabel!.text != sender.titleLabel!.text)
//            {
//                button.unSelectedState()
//            } else {
//                button.selectedState()
//            }
//            buttons.filter{$0 != button}
//        }
//
        
        
        styleSelected = sender.titleLabel!.text
        
        if (styleArray.contains(styleSelected)) {
            styleArray = styleArray.filter{$0 != styleSelected}
            
            switch (styleSelected) {
            case "Add":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x41, 0x0, 0x0, 0x0, 0x24, 0x1, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
                break;
            case .none:
                break;
            case .some(_):
                break;
            }
            
        } else {
            styleArray.append(styleSelected)
            
            switch (styleSelected) {
            case "Add":
                GeneratorManager.sharedInstance.sendData(arr:
                    [0x1, 0x0, 0x0, 0x0, 0x41, 0x0, 0x0, 0x0, 0x14, 0x1, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0]
                )
                break;
            case .none:
                break;
            case .some(_):
                break;
            }
        }
        
        //        styleSelected = button.titleLabel!.text
        //
        //        if (styleArray.contains(styleSelected)) {
        //            styleArray = styleArray.filter{$0 != styleSelected}
        //        } else {
        //            styleArray.append(styleSelected)
        //        }
        //
        //        UserDefaults.standard.set(styleArray, forKey: "styleArray")
        
    }
    
    func getValue() -> String? {
        print(">", styleSelected)
        return styleSelected!
    }
}
