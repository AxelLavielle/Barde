//
//  File.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class StyleViewController: UIViewController {
    
    @IBOutlet weak var styleScrollView: UIScrollView!

    var styleSelected: String! = ""
    
    var styleArray: [String] = []

    override func viewDidLoad() {

        super.viewDidLoad()
        
        let styles = StyleService().getAll()
        var x = 8
        var y = 0
        
        
        styles?.forEach{style in
            y += 50
            
            let button = CheckButton(frame: CGRect(x: Int(x), y: y, width: 300, height: 30))
            button.layer.borderColor = UIColor.white.cgColor
            button.setTitle(style.name, for: [])
            
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
    
    @objc func buttonAction(_ button: CheckButton) {
        
        styleSelected = button.titleLabel!.text
        
        if (styleArray.contains(styleSelected)) {
            styleArray = styleArray.filter{$0 != styleSelected}
            
            switch (styleSelected) {
            case "Jazz":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x57, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
                break;
            case "Blues":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
                break;
            case .none:
                break;
            case .some(_):
                break;
            }
            
        } else {
            styleArray.append(styleSelected)
            
            switch (styleSelected) {
            case "Jazz":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 111, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
                break;
            case "Blues":
                GeneratorManager.sharedInstance.sendData(arr: [0x1, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 211, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
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
