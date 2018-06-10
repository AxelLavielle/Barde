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

    var styleSelected: String! = "ok"

    override func viewDidLoad() {

        super.viewDidLoad()
        
        let styles = StyleService().getAll()
        var x = 8
        var y = 0
        
        
        
        styles?.forEach{style in
            y += 50
            
            let button = CheckButton(frame: CGRect(x: Int(x), y: y, width: 343, height: 30))
            button.layer.borderColor = UIColor.white.cgColor
            button.setTitle(style.name, for: [])
            
            self.styleScrollView.addSubview(button)
            
            button.topAnchor.constraint(equalTo: styleScrollView.topAnchor, constant: 50).isActive = true
            button.bottomAnchor.constraint(equalTo: styleScrollView.bottomAnchor, constant:410).isActive = true
            button.trailingAnchor.constraint(equalTo: styleScrollView.trailingAnchor, constant: 0).isActive = true
            button.centerXAnchor.constraint(equalTo: styleScrollView.centerXAnchor, constant: 0).isActive = true
            
            button.addTarget(self, action: #selector(buttonAction(_:)), for: .touchUpInside)
            
            }
        
    }
    
    @objc func buttonAction(_ button: CheckButton) {
        
        styleSelected = button.titleLabel!.text
        print("1", styleSelected)

        
    }
    
    func getValue() -> String? {
        print(">", styleSelected)
        return styleSelected!
    }
}
