extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{Data, DeriveInput, Fields, FieldsNamed, Ident};

fn get_fields(data: &Data) -> FieldsNamed {
    if let Data::Struct(strct) = data {
        if let Fields::Named(fields) = &strct.fields {
            fields.to_owned()
        } else {
            panic!("Can only handle named fields")
        }
    } else {
        panic!("Can only handle structs");
    }
}

fn impl_bean(ast: DeriveInput) -> TokenStream {
    let ident = ast.ident;
    let fields = get_fields(&ast.data);
    let setters = fields.named.iter().map(|field| {
        let name = field.ident.as_ref().unwrap();
        let ty = &field.ty;
        let f_name: proc_macro2::TokenStream = format!("set_{}", name).parse().unwrap();
        let function_signature = quote!(pub fn #f_name (&mut self, input: #ty));
        quote!(
            #function_signature {
                self.#name = input;
            }
        )
    });

    let getters = fields.named.iter().map(|field| {
        let name = field.ident.as_ref().unwrap();
        let ty = &field.ty;
        let function_signature = quote!(pub fn #name (&self) -> &#ty);
        quote!(
            #function_signature {
                &self.#name
            }
        )
    });

    quote! {
        impl #ident {
            #(#setters)*
            #(#getters)*
        }
    }
    .into()
}

#[proc_macro_derive(Bean)]
pub fn my_macro_bean_derive(input: TokenStream) -> TokenStream {
    let ast: DeriveInput = syn::parse(input).unwrap();

    impl_bean(ast)
}

fn impl_deserialize_struct(data: &Data, ident: Ident) -> TokenStream {
    let fields = get_fields(data);

    let fields_getters = fields.named.iter().map(|field| {
        let name = field.ident.as_ref().unwrap();
        let ty = &field.ty;
        let param: proc_macro2::TokenStream = format!("\"{}\"", name).parse().unwrap();
        let err_msg: proc_macro2::TokenStream =
            format!("\"field {} not found\"", name).parse().unwrap();
        quote!(#name: #ty::from_value(obj.get(#param).ok_or(#err_msg)?)?)
    });

    quote! {
        impl zappy_json::DeserializeTrait for #ident {
            fn from_value(value: &zappy_json::JsonValue) -> Result<#ident, String>
            where
                Self: Sized {
                    match value {
                        zappy_json::JsonValue::Object(obj) => {
                            Ok(#ident {
                                #(#fields_getters),*
                            })
                        },
                        _ => return Err(String::from("Not a json object"))
                    }
                }
        }
    }
    .into()
}

fn impl_deserialize(ast: DeriveInput) -> TokenStream {
    let ident = ast.ident;
    let data = &ast.data;

    match data {
        Data::Struct(_) => impl_deserialize_struct(data, ident),
        _ => panic!("Can only handle structs"),
    }
}

#[proc_macro_derive(Deserialize)]
pub fn my_macro_deserialize_derive(input: TokenStream) -> TokenStream {
    let ast: DeriveInput = syn::parse(input).unwrap();

    impl_deserialize(ast)
}
