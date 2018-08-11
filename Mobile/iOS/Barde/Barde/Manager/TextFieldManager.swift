//
//  TextFieldManager.swift
//  Barde
//
//  Created by Arnaud Perrault on 09/08/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class TextFieldManager: NSObject {
    static let sharedInstance = TextFieldManager()

    // When focussed - show gray border
    func highlightSelected(textfield: UITextField){
       
        textfield.attributedPlaceholder = NSAttributedString(string: textfield.placeholder!,
                                                          attributes: [NSAttributedStringKey.foregroundColor: UIColor.gray])

    }
    
    func removeErrorHighlight(textField: UITextField){
        
        textField.attributedPlaceholder = NSAttributedString(string: textField.placeholder!,
                                                             attributes: [NSAttributedStringKey.foregroundColor: UIColor.gray])
    }
    
    func errorHighlight(textField: UITextField){
        
        textField.attributedPlaceholder = NSAttributedString(string: textField.placeholder!,
                                                             attributes: [NSAttributedStringKey.foregroundColor: UIColor.red])
    }
}
