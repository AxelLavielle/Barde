//
//  SignupViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 19/12/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import Alamofire
import SwiftyJSON

class SignupViewController: UIViewController {
    
    @IBOutlet weak var scrollView: UIScrollView!
    @IBOutlet weak var firstnameTextField: UITextField!
    @IBOutlet weak var lastnameTextField: UITextField!
    @IBOutlet weak var birthdateTextField: UITextField!
    @IBOutlet weak var usernameTextField: UITextField!
    @IBOutlet weak var emailTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    @IBOutlet weak var confirmPasswordTextField: UITextField!
    @IBOutlet weak var passwordImageView: UIImageView!
    @IBOutlet weak var confirmPasswordImageView: UIImageView!
    
    let datePicker = UIDatePicker()
    
    func createDatePicker() {
        datePicker.datePickerMode = .date
        datePicker.maximumDate = Date.init()
        
        birthdateTextField.inputView = datePicker
        datePicker.addTarget(self, action: #selector(datePickerValueChanged(_:)), for: .valueChanged)
    }
    
    @objc func datePickerValueChanged(_ sender: Any) {
        let dateFormatter = DateFormatter()
        
        dateFormatter.dateStyle = .short
        dateFormatter.timeStyle = .none
        dateFormatter.dateFormat = "MM/dd/YYYY"
        
        birthdateTextField.text = dateFormatter.string(from: datePicker.date)
    }

    
    override func viewDidLoad() {
        
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: Notification.Name.UIKeyboardWillHide, object: nil)
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: Notification.Name.UIKeyboardWillChangeFrame, object: nil)
        
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(dismissKeyboard))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
        
        configureView()
        createDatePicker()
    }
    
    @objc func dismissKeyboard(){
        view.endEditing(true)
    }
    
    @objc func adjustForKeyboard(notification: Notification) {
        let userInfo = notification.userInfo!
        
        let keyboardScreenEndFrame = (userInfo[UIKeyboardFrameEndUserInfoKey] as! NSValue).cgRectValue
        let keyboardViewEndFrame = view.convert(keyboardScreenEndFrame, from: view.window)
        
        if notification.name == Notification.Name.UIKeyboardWillHide {
            scrollView.contentInset = UIEdgeInsets.zero
        } else {
            scrollView.contentInset = UIEdgeInsets(top: 0, left: 0, bottom: keyboardViewEndFrame.height, right: 0)
        }
    }
    
    
    func signUp() {
        
        if (checkIfEmpty(str: confirmPasswordTextField.text!) || checkIfEmpty(str: emailTextField.text!) || checkIfEmpty(str: passwordTextField.text!))
        {
            Alert.showRequiredField(on: self)
        }
        else
        {
            
            if let password = passwordTextField.text {
                if let confirmPassword = confirmPasswordTextField.text {
                    
                    if (password != confirmPassword)
                    {
                        Alert.showBasic(on: self, with: NSLocalizedString("WrongContent.text", comment: ""), message: NSLocalizedString("WrongContentDescription.text", comment: ""))
                    }
                    else
                    {
                        let parameters: Parameters = [
                            "email":  emailTextField.text ?? "",
                            "password": passwordTextField.text ?? "",
                            "firstName": firstnameTextField.text ?? "",
                            "lastName": lastnameTextField.text ?? "",
                            "userName": usernameTextField.text ?? "",
                            "yearOfBirth": (birthdateTextField.text != "" ? getSubstr(str: birthdateTextField.text!, indexStart: 6, indexEnd: 0) : ""),
                            "monthOfBirth": (birthdateTextField.text != "" ? getSubstr(str: birthdateTextField.text!, indexStart: 0, indexEnd: -8) : ""),
                            "dayOfBirth": (birthdateTextField.text != "" ? getSubstr(str: birthdateTextField.text!, indexStart: 3, indexEnd: -5) : ""),
                            ]
                        
                        
                        Alamofire.request(Utils().getApiUrl() + "/auth/register", method:.post, parameters: parameters).responseJSON { response in
                            
                            if let httpStatusCode = response.response?.statusCode {
                                
                                let data = JSON(response.result.value!)

                                switch(httpStatusCode) {
                                case 200:
                                    let parameters: Parameters = [
                                        "email":  self.emailTextField.text ?? "",
                                        "password": self.passwordTextField.text ?? "",
                                        ]
                                    
                                    Alamofire.request(Utils().getApiUrl() + "/auth/login", method:.post, parameters: parameters).responseJSON { response in
                                        
                                        if let httpStatusCode = response.response?.statusCode {
                                            switch(httpStatusCode) {
                                            case 200:
                                                
                                                if ((response.result.value) != nil) {
                                                    let data = JSON(response.result.value!)
                                                    
                                                    UserDefaults.standard.set(data["data"]["token"].stringValue, forKey: "Token")
                                                    UserDefaults.standard.set(self.emailTextField.text, forKey: "Email")
                                                    self.performSegue(withIdentifier: "ToMainView", sender: self)
                                                }
                                                break
                                            case 400:
                                                let refreshAlert = UIAlertController(title: data["msg"].stringValue, message: data["data"]["message"].stringValue, preferredStyle: UIAlertControllerStyle.alert)
                                                
                                                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                                                }))
                                                
                                                self.present(refreshAlert, animated: true, completion: nil)
                                                break
                                            default:
                                                print("default")
                                                
                                            }
                                        }
                                    }
                                    break
                                case 400:
                                    let refreshAlert = UIAlertController(title: data["msg"].stringValue, message: data["data"]["message"].stringValue, preferredStyle: UIAlertControllerStyle.alert)
                                    
                                    refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                                    }))
                                    
                                    self.present(refreshAlert, animated: true, completion: nil)
                                    break
                                case 409:
                                    let refreshAlert = UIAlertController(title: data["msg"].stringValue, message: data["data"]["message"].stringValue, preferredStyle: UIAlertControllerStyle.alert)
                                    
                                    refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                                    }))
                                    
                                    self.present(refreshAlert, animated: true, completion: nil)
                                    break
                                default:
                                    print("default")
                                    
                                }
                            }
                            
                        }
                    }
                }
            }
        }
    }
    
    func checkIfEmpty(str: String) -> Bool {
        if str.isEmpty {
            return true
        }
        return false
    }
    
    func getSubstr(str: String, indexStart: Int, indexEnd: Int) -> String {
        
        let start = str.index(str.startIndex, offsetBy: indexStart)
        let end = str.index(str.endIndex, offsetBy: indexEnd)
        let range = start..<end
        
        print(">>", str[range])
       
        return String(str[range])
    }
    
    func configureView()
    {
        let firstNamePaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        firstnameTextField.leftView = firstNamePaddingView
        firstnameTextField.leftViewMode = .always
        
        let lastnamePaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        lastnameTextField.leftView = lastnamePaddingView
        lastnameTextField.leftViewMode = .always
        
        let birthDatePaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        birthdateTextField.leftView = birthDatePaddingView
        birthdateTextField.leftViewMode = .always
        
        let usernamePaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        usernameTextField.leftView = usernamePaddingView
        usernameTextField.leftViewMode = .always
        
        let emailPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        emailTextField.leftView = emailPaddingView
        emailTextField.leftViewMode = .always
        
        let passwordPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        passwordTextField.leftView = passwordPaddingView
        passwordTextField.leftViewMode = .always
        
        let confirmPasswordPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        confirmPasswordTextField.leftView = confirmPasswordPaddingView
        confirmPasswordTextField.leftViewMode = .always
        
        let passwordTapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(passwordIvAction(tapGestureRecognizer:)))
        passwordImageView.isUserInteractionEnabled = true
        passwordImageView.addGestureRecognizer(passwordTapGestureRecognizer)
        
        let confirmPasswordTapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(confirmPasswordIvAction(tapGestureRecognizer:)))
        confirmPasswordImageView.isUserInteractionEnabled = true
        confirmPasswordImageView.addGestureRecognizer(confirmPasswordTapGestureRecognizer)
    }
    
    @IBAction func textFieldTouchDown(_ sender: UITextField) {
        TextFieldManager.sharedInstance.highlightSelected(textfield: sender)
    }
    
    @IBAction func textFieldEditingDidEnd(_ sender: UITextField) {
        
        if(sender.text?.trimmingCharacters(in: .whitespacesAndNewlines) == ""){
            TextFieldManager.sharedInstance.errorHighlight(textField: sender)
        }
        else {
            TextFieldManager.sharedInstance.removeErrorHighlight(textField: sender)
        }
    }
    
    
    @IBAction func signupButtonAction(_ sender: Any) {
        signUp()
    }
    
    
    @IBAction func buttonClose(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @objc func passwordIvAction(tapGestureRecognizer: UITapGestureRecognizer)
    {
        _ = tapGestureRecognizer.view as! UIImageView
        
        passwordTextField.isSecureTextEntry = !passwordTextField.isSecureTextEntry
    }
    
    @objc func confirmPasswordIvAction(tapGestureRecognizer: UITapGestureRecognizer)
    {
        _ = tapGestureRecognizer.view as! UIImageView
        
        confirmPasswordTextField.isSecureTextEntry = !confirmPasswordTextField.isSecureTextEntry
    }
}
