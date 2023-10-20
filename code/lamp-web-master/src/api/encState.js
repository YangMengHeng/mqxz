import axiosApi from './AxiosApi.js'


const apiList = {
  page: {
    method: 'POST',
    url: `/job/nodeState/page`,
  
  },

//---------------------------------------------------------------------------------------
  update: {
    method: 'PUT',
    url: `/job/nodeState`
    //url:'/ecn/ecnupdate'                       //修改
  },


//----------------------------------------------------------------------------------------

  save: {
    method: 'POST',
    url: `/job/nodeState`
     //url:'/ecn/ecnadd'               //新增
  },


  //=====================================================================================
  delete: {
    method: 'DELETE',
    url: `/job/nodeState`
    //url: `/ecn/ecndelect`                            //删除
  },

  //=====================================================================================
  preview: {
    method: 'POST',
    url: `/job/nodeState/preview`
  },
  export: {
    method: 'POST',
    url: `/job/nodeState/export`
  },
  import: {
    method: 'POST',
    url: `/job/nodeState/import`
    //url:'/ecn/ecnadd'               //新增                                
  }
}






export default {
  page (data, custom = {}) {
    return axiosApi({
      ...apiList.page,
      data,
      custom
    })
  },
  save (data) {
    return axiosApi({
      ...apiList.save,
      data
    })
  },


//--------------------------------------------------------
  update (data) {
    return axiosApi({
      ...apiList.update,
      data
    })
  },

//---------------------------------------------------------


  delete (data) {
   
    return axiosApi({
      ...apiList.delete,
      data
    })
  },
  preview (data) {
    return axiosApi({
      ...apiList.preview,
      data
    })
  },
  export (data) {
    return axiosApi({
      ...apiList.export,
      responseType: "blob",
      data
    })
  },
  import (data) {
    return axiosApi({
      ...apiList.import,
      data
    })                          //新增
  }
}
